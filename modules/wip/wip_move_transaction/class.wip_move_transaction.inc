<?php

class wip_move_transaction extends dbObject {

 public static $table_name = "wip_move_transaction";
 public static $primary_column = "wip_move_transaction_id";
 public static $dependent_classes = ['wip_wo_routing_line', 'wip_wo_routing_detail'];
 public static $key_column = 'wip_wo_header_id';
 public static $module = "wip";
 public static $allowed_inv_transactions = [
		 '1' => 'Miscellaneous Issue',
		 '2' => 'Miscellaneous Receipt',
		 '3' => 'Subinventory Transfer'
 ];
//  data base variables as stored database column name
 public $field_a = [
		 'wip_move_transaction_id',
		 'wip_wo_header_id',
		 'org_id',
		 'wo_number',
		 'item_number',
		 'item_id',
		 'from_routing_sequence',
		 'to_routing_sequence',
		 'from_operation_step',
		 'to_operation_step',
		 'transaction_type',
		 'transaction_date',
		 'move_quantity',
		 'reason',
		 'reference',
		 'scrap_account_id',
		 'sales_order_header_id',
		 'sales_order_line_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
//variables used for showing data
 public $initial_search = [
		 'wip_move_transaction_id',
		 'wip_wo_header_id',
		 'org_id',
		 'wo_number',
		 'item_number',
		 'item_id'
 ];
 public $column = [
		 'wip_move_transaction_id',
		 'wip_wo_header_id',
		 'org_id',
		 'wo_number',
		 'item_number',
		 'item_id',
		 'from_routing_sequence',
		 'to_routing_sequence',
		 'transaction_date',
		 'move_quantity'
 ];
 public $account = [
		 'scrap_account_id'
 ];
 public $fields_inForm_notInDataBase = [
		 'remaining_quantity',
		 "item_description",
		 "uom",
		 'available_quantity',
		 'total_quantity'
 ];
 public $requiredField = [
		 'wip_wo_header_id',
		 'org_id',
		 'from_routing_sequence',
		 'to_routing_sequence',
		 'from_operation_step',
		 'to_operation_step',
		 'transaction_type',
		 'transaction_date',
		 'move_quantity'
 ];
 public $wip_move_transaction_id;
 public $wip_wo_header_id;
 public $wo_routing_line_id;
 public $wo_routing_detail_id;
 public $org_id;
 public $wo_number;
 public $item_number;
 public $item_id;
 public $from_routing_sequence;
 public $to_routing_sequence;
 public $from_operation_step;
 public $to_operation_step;
 public $transaction_type;
 public $transaction_date;
 public $move_quantity;
 public $reason;
 public $reference;
 public $scrap_account_id;
 public $sales_order_header_id;
 public $sales_order_line_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $msg;
 public $remaining_quantity;
 public $item_description;
 public $uom;
 public $total_quantity;
 public $available_quantity;

 Public static function wip_transactions() {
	$option_header = option_header::find_by_name('WIP_TRANSACTIONS');
	$wip_transactions = option_line::find_by_option_id($option_header->option_header_id);
	return $wip_transactions;
 }

 private function wipMove_Resource_Transaction($routing_details, $charge) {
	$wip_resource_transaction = new wip_resource_transaction;
	foreach ($wip_resource_transaction->field_a as $key => $value) {
	 if (!empty($routing_details->$value)) {
		$wip_resource_transaction->$value = $routing_details->$value;
	 }
	}
//	$wip_resource_transaction->wip_wo_routing_detail_id = $routing_details->wip_wo_routing_detail_id;
	$wip_resource_transaction->org_id = $this->org_id;
	$wip_resource_transaction->transaction_type = 'WIP_RESOURCE_TRANSACTION';
	$wip_resource_transaction->reference = $this->wip_wo_header_id;
	$time = time();
	$wip_resource_transaction->transaction_date = strftime("%Y-%m-%d %H:%M:%S", $time);

	if ($charge === 1) {
	 $wip_resource_transaction->transaction_quantity = $this->move_quantity * $routing_details->resource_usage;
	} elseif ($charge === -1) {
	 $wip_resource_transaction->transaction_quantity = -($this->move_quantity * $routing_details->resource_usage);
	}
	try {
	 $wip_resource_transaction->audit_trial();
	 $wip_resource_transaction->save();
	 $wip_resource_transaction->_after_save();
	 echo "<br> Resource Transaction is sucessfully updated";
	} catch (Exception $e) {
	 echo "<br> Resource Transaction Update Failed! @  " . __LINE__ . ' ' . $e->getMessage();
	}
 }

 public function update_moveTransaction_andAll($bom_lines, $toOrFrom, $transaction_type_id = 6) {
	$quantity = $this->move_quantity * $bom_lines->usage_quantity;

	$inv_transaction = new inv_transaction();
	foreach ($inv_transaction->field_a as $key => $value) {
	 $inv_transaction->$key = NULL;
	}
	$inv_transaction->transaction_type_id = $transaction_type_id;
	$inv_transaction->item_id = $bom_lines->component_item_id;
	$inv_transaction->org_id = $this->org_id;
	$inv_transaction->quantity = $this->move_quantity * $bom_lines->usage_quantity;

	if ($toOrFrom == 'from') {
	 $inv_transaction->from_subinventory_id = $bom_lines->supply_sub_inventory;
	 $inv_transaction->from_locator_id = $bom_lines->supply_locator;
	} elseif ($toOrFrom == 'to') {
	 $inv_transaction->to_subinventory_id = $bom_lines->supply_sub_inventory;
	 $inv_transaction->to_locator_id = $bom_lines->supply_locator;
	}

	$item = item::find_by_id($bom_lines->component_item_id);
	$inv_transaction->item_number = $item->item_number;
	$inv_transaction->uom_id = $item->uom_id;
	$inv_transaction->document_type = 'Work Order';
	$inv_transaction->document_number = $this->wo_number;
	$inv_transaction->document_id = $this->wip_wo_header_id;
	$inv_transaction->reference = 'wip_wo_header_id';
	$inv_transaction->wip_wo_header_id = $this->wip_wo_header_id;
	$inv_transaction->audit_trial();
	$inv_transaction_satus = $inv_transaction->save();
	$inv_transaction->_after_save();
	if ($inv_transaction_satus == 1) {
	 //update issued quantity
	 $update_wo_bom_class = new wip_wo_bom();
	 $update_wo_bom_class->wip_wo_bom_id = $bom_lines->wip_wo_bom_id;

	 if ($toOrFrom == 'from') {
		$update_wo_bom_class->issued_quantity = $quantity + $bom_lines->issued_quantity;
	 } elseif ($toOrFrom == 'to') {
		$update_wo_bom_class->issued_quantity = $bom_lines->issued_quantity - $quantity;
	 }
	 $update_wo_bom_class->audit_trial();
	 $update_wo_bom_class->save();
	}
 }

 private function _update_fromOperation($wwrl_from) {
	
 }

 public function _after_save() {

	//Insert in WIP WO BOM - item issues for operational pull
	if ((!empty($this->wip_move_transaction_id)) && (!(empty($this->from_routing_sequence))) && (!(empty($this->to_routing_sequence)))) {
	 $wip_wo_header_id = $this->wip_wo_header_id;

	 //instantiate from & to operation line clases
	 $wwrl_from = new wip_wo_routing_line();
	 $wwrl_from->wip_wo_header_id = $this->wip_wo_header_id;
	 $wwrl_from->routing_sequence = $this->from_routing_sequence;
	 $wwrl_from_i = $wwrl_from->findBy_woHeaderId_routingSeq();
	 $wwrl_from->wip_wo_routing_line_id = $wwrl_from_i->wip_wo_routing_line_id;
	 $from_operation_step = $this->from_operation_step . '_quantity';

	 //start to opartion 
	 $wwrl_to = new wip_wo_routing_line();
	 $wwrl_to->wip_wo_header_id = $this->wip_wo_header_id;
	 $wwrl_to->routing_sequence = $this->to_routing_sequence;
	 $wwrl_to_i = $wwrl_to->findBy_woHeaderId_routingSeq();
	 $wwrl_to->wip_wo_routing_line_id = $wwrl_to_i->wip_wo_routing_line_id;
	 $to_operation_step = $this->to_operation_step . '_quantity';

	 /*
		* 1. start of from opertion quantity update
		*/
	 // $this->_update_fromOperation(&$wwrl_from);
	 if (isset($wwrl_from_i->$from_operation_step)) {
		$begining_from_quantity = $wwrl_from_i->$from_operation_step;
	 }
	 $end_from_quantity = $begining_from_quantity - $this->move_quantity;
	 $wwrl_from->$from_operation_step = $end_from_quantity;
	 try {
		$wwrl_from->audit_trial();
		$wwrl_from->save();
		echo "<br> From routing line quantity is sucessfully updated";
	 } catch (Exception $e) {
		echo "<br> From routing line quantity update failed! @  " . __LINE__ . ' ' . $e->getMessage();
	 }


	 /*
		 2. Begining of WIP BOM, Routing Detail (Resource Charge) and Inventory Transaction (Onhand) Update.
		*/
	 $from_routing_sequence = $this->from_routing_sequence;
	 $to_routing_sequence = $this->to_routing_sequence;
	 $from_routing_step = $this->from_operation_step;
	 $to_routing_step = $this->to_operation_step;
	 $wwb = new wip_wo_bom();
	 $wwb->wip_wo_header_id = $wip_wo_header_id;

	 //Moving from 10 to 10 OR 20 to 20
	 if (($from_routing_sequence == $to_routing_sequence ) && ( $from_routing_step != $to_routing_step)) {
		//check if auto count & backflush is enabled
		if (($wwrl_from_i->count_point_cb == 1) && ($wwrl_from_i->backflush_cb == 1)) {
		 $wwb->routing_sequence = $from_routing_sequence;
		 $all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
		 if (($from_routing_step == 'queue') && (!empty($all_wo_bom_lines))) {
			//back flush
			foreach ($all_wo_bom_lines as $bom_lines) {
			 //reduce onhand
			 if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				$this->update_moveTransaction_andAll($bom_lines, 'from', $transaction_type_id = 6);
			 }
			}
		 } elseif (($to_routing_step == 'queue') && (!empty($all_wo_bom_lines))) {
			//return back flush
			foreach ($all_wo_bom_lines as $bom_lines) {
			 if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				$this->update_moveTransaction_andAll($bom_lines, 'to', $transaction_type_id = 7);
			 }
			}
		 }
		}

		/* Resource Charges
		 * 1. Check if auto charge & count point is enabled
		 * 2. If moved from Queue then resource is charged
		 * 3. If move out of Queue resource charged is removed */
		if (($wwrl_from_i->count_point_cb == 1) && ($wwrl_from_i->auto_charge_cb == 1)) {
		 $all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($wwrl_from_i->wip_wo_routing_line_id);

		 if ($from_routing_step == 'queue') {
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, 1);
			 }
			}
		 } elseif ($to_routing_step == 'queue') {
			//return back flush
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, -1);
			 }
			}
		 }
		}
	 }

	 /* Moving from 10 to 30 OR 20 to 50, etc
		* 2.1. For the movement between same sequence i.e 10 to 10 or 10 to 20
		* 2.2. Movement between two end operations i.e 10 to 30
		* 2.3. End operation 30 Que to Run
		*/

	 if (($from_routing_sequence < $to_routing_sequence)) {
		//$from_routing_sequence transactions check if auto count & backflush is enabled
		if (($wwrl_from_i->count_point_cb == 1) && ($wwrl_from_i->backflush_cb == 1)) {
		 $wwb->routing_sequence = $from_routing_sequence;
		 $all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
		 if (($from_routing_step == 'queue') && (!empty($all_wo_bom_lines))) {
			//back flush
			foreach ($all_wo_bom_lines as $bom_lines) {
			 //reduce onhand
			 if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				$this->update_moveTransaction_andAll($bom_lines, 'from', $transaction_type_id = 6);
			 }
			}
		 }
		}
		//Resource Charges
		if (($wwrl_from_i->count_point_cb == 1) && ($wwrl_from_i->auto_charge_cb == 1)) {
		 $all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($wwrl_from_i->wip_wo_routing_line_id);
		 if ($from_routing_step == 'queue') {
			//back flush
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, 1);
			 }
			}
		 }
		}

		//all inbetween routing lines
		$all_inBetween_routingSteps = wip_wo_routing_line::find_by_wipWoHeaderId_and_fromToRoutingSequence($wip_wo_header_id, $from_routing_sequence, $to_routing_sequence);
		foreach ($all_inBetween_routingSteps as $inbtween_routing_lines) {
		 //$to_routing_sequence transactions check if auto count & backflush is enabled
		 if (($inbtween_routing_lines->count_point_cb == 1) && ($inbtween_routing_lines->backflush_cb == 1)) {
			$wwb->routing_sequence = $inbtween_routing_lines->routing_sequence;
			$all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
			//back flush
			if (!empty($all_wo_bom_lines)) {
			 foreach ($all_wo_bom_lines as $bom_lines) {
				//reduce onhand
				if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				 $this->update_moveTransaction_andAll($bom_lines, 'from', $transaction_type_id = 6);
				}
			 }
			}
		 }
		}
		//Resource Charges
		foreach ($all_inBetween_routingSteps as $inbtween_routing_lines) {
		 if (($inbtween_routing_lines->count_point_cb == 1) && ($inbtween_routing_lines->auto_charge_cb == 1)) {
			$all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($inbtween_routing_lines->wip_wo_routing_line_id);
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, 1);
			 }
			}
		 }
		}

		//$to_routing_sequence transactions check if auto count & backflush is enabled
		if (($wwrl_to_i->count_point_cb == 1) && ($wwrl_to_i->backflush_cb == 1)) {
		 $wwb->routing_sequence = $to_routing_sequence;
		 $all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
		 if (($to_routing_step != 'queue') && (!empty($all_wo_bom_lines))) {
			//back flush
			foreach ($all_wo_bom_lines as $bom_lines) {
			 //reduce onhand
			 if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				$this->update_moveTransaction_andAll($bom_lines, 'from', $transaction_type_id = 6);
			 }
			}
		 }
		}
		//resource Charges
		if (($wwrl_to_i->count_point_cb == 1) && ($wwrl_to_i->auto_charge_cb == 1)) {
		 $all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($wwrl_to_i->wip_wo_routing_line_id);
		 if ($to_routing_step != 'queue') {
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, 1);
			 }
			}
		 }
		}
	 }

	 //Moving from 50 to 20 OR 40 to 10, etc
	 if (($from_routing_sequence > $to_routing_sequence)) {

		//$from_routing_sequence transactions check if auto count & backflush is enabled
		if (($wwrl_from_i->count_point_cb == 1) && ($wwrl_from_i->backflush_cb == 1)) {
		 $wwb->routing_sequence = $from_routing_sequence;
		 $all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
		 pa($all_wo_bom_lines);
		 if (($from_routing_step != 'queue') && (!empty($all_wo_bom_lines))) {
			//back flush
			foreach ($all_wo_bom_lines as $bom_lines) {
			 //reduce onhand
			 if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				$this->update_moveTransaction_andAll($bom_lines, 'to', $transaction_type_id = 7);
			 }
			}
		 }
		}
		//Resource Charges
		if (($wwrl_from_i->count_point_cb == 1) && ($wwrl_from_i->auto_charge_cb == 1)) {
		 $all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($wwrl_from_i->wip_wo_routing_line_id);
		 if ($from_routing_step != 'queue') {
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, -1);
			 }
			}
		 }
		}

		//all inbetween routing lines
		$all_inBetween_routingSteps = wip_wo_routing_line::find_by_wipWoHeaderId_and_fromToRoutingSequence($wip_wo_header_id, $to_routing_sequence, $from_routing_sequence);
		foreach ($all_inBetween_routingSteps as $inbtween_routing_lines) {
		 //$to_routing_sequence transactions check if auto count & backflush is enabled
		 if (($inbtween_routing_lines->count_point_cb == 1) && ($inbtween_routing_lines->backflush_cb == 1)) {
			$wwb->routing_sequence = $inbtween_routing_lines->routing_sequence;
			$all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
			//back flush
			if (!empty($all_wo_bom_lines)) {
			 foreach ($all_wo_bom_lines as $bom_lines) {
				//reduce onhand
				if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				 $this->update_moveTransaction_andAll($bom_lines, 'to', $transaction_type_id = 7);
				}
			 }
			}
		 }
		}
		//in bewteen Resource Charges
		foreach ($all_inBetween_routingSteps as $inbtween_routing_lines) {
		 if (($inbtween_routing_lines->count_point_cb == 1) && ($inbtween_routing_lines->auto_charge_cb == 1)) {
			$all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($inbtween_routing_lines->wip_wo_routing_line_id);
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, -1);
			 }
			}
		 }
		}

		//$to_routing_sequence transactions check if auto count & backflush is enabled
		if (($wwrl_to_i->count_point_cb == 1) && ($wwrl_to_i->backflush_cb == 1)) {
		 $wwb->routing_sequence = $to_routing_sequence;
		 $all_wo_bom_lines = $wwb->findBy_woHeaderId_routingSeq();
		 if (($to_routing_step == 'queue') && (!empty($all_wo_bom_lines))) {
			//back flush
			foreach ($all_wo_bom_lines as $bom_lines) {
			 //reduce onhand
			 if ($bom_lines->wip_supply_type == 'OPERATION_PULL') {
				$this->update_moveTransaction_andAll($bom_lines, 'to', $transaction_type_id = 7);
			 }
			}
		 }
		}
		//resource Charges
		if (($wwrl_to_i->count_point_cb == 1) && ($wwrl_to_i->auto_charge_cb == 1)) {
		 $all_routing_details = wip_wo_routing_detail::find_by_wipWo_lineId($wwrl_to_i->wip_wo_routing_line_id);
		 if ($to_routing_step == 'queue') {
			foreach ($all_routing_details as $routing_details) {
			 //charge resource
			 if ($routing_details->charge_type == 'WIP_MOVE') {
				$this->wipMove_Resource_Transaction($routing_details, -1);
			 }
			}
		 }
		}
	 }

	 /*
		 3. start of from opartion quantity update
		*/
	 if (isset($wwrl_to_i->$to_operation_step)) {
		$begining_to_quantity = $wwrl_to_i->$to_operation_step;
	 } else {
		$begining_to_quantity = 0;
	 }
	 $end_to_quantity = $begining_to_quantity + $this->move_quantity;
	 $wwrl_to->$to_operation_step = $end_to_quantity;
	 try {
		$wwrl_to->audit_trial();
		$wwrl_to->save();
		echo "<br> To routing line quantity is sucessfully updated";
	 } catch (Exception $e) {
		echo "<br> To routing line quantity update failed! @  " . __LINE__ . ' ' . $e->getMessage();
	 }
	}
 }

 public function _before_showing() {
	
 }

 public function _before_save() {
	$primary_column = static::$primary_column;
	if (empty($this->$primary_column)) {
	 return 1;
	} else {
	 echo '<div class="message"> You are not allowed to update a completed move transaction!</div>';
	 return -99;
	}
 }

}

//end of resource class
?>



