<?php

class wip_resource_transaction extends dbObject {

 public static $table_name = "wip_resource_transaction";
 public static $dependent_classes = ['wip_wo_bom', 'wip_wo_routing_line', 'wip_wo_routing_detail'];
 public static $primary_column = "wip_resource_transaction_id";
 public static $key_column = 'wip_wo_routing_detail_id';
 public static $module = "wip";
 public static $gl_journal_category = "WIP_RESOURCE";
//  data base variables as stored database column name
 public $field_a = [
		 'wip_resource_transaction_id',
		 'wip_wo_routing_line_id',
		 'wip_wo_routing_detail_id',
		 'wip_wo_header_id',
		 'org_id',
		 'transaction_type',
		 'transaction_date',
		 'transaction_quantity',
		 'reason',
		 'reference',
		 'scrap_account_id',
		 'sales_order_header_id',
		 'sales_order_line_id',
		 'gl_journal_header_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
//variables used for showing data
 public $initial_search = [
		 'wip_resource_transaction_id',
		 'wip_wo_header_id',
		 'org_id',
		 'wo_number',
		 'item_number',
		 'item_id'
 ];
 public $column = [
		 'wip_resource_transaction_id',
		 'wip_wo_header_id',
		 'org_id',
		 'wo_number',
		 'item_number',
		 'item_id',
		 'transaction_date',
		 'transaction_quantity'
 ];
 public $account = [
		 'scrap_account_id'
 ];
 public $fields_inForm_notInDataBase = [
		 'remaining_quantity',
		 'item_id',
		 'item_number',
		 "item_description",
		 "uom",
		 'available_quantity',
		 'total_quantity',
		 'department_id'
 ];
 public $fields_inHeader_needsToBeInserted_inPOST = [
		 'org_id',
		 'transaction_type',
		 'transaction_date'
 ];
 public $requiredField = [
		 'wip_wo_routing_line_id',
		 'wip_wo_routing_detail_id',
		 'wip_wo_header_id',
		 'org_id',
		 'transaction_type',
		 'transaction_date',
		 'transaction_quantity'
 ];
 public $search = [
		 '_show_update_path' => 1,
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " Resource Trnx - WIP Work Order  Resource Transaction "; //page Title
 public $option_lists = [
//		 'wip_wo_type' => 'WIP_WO_TYPE',
//		 'wip_wo_status' => 'WIP_WO_STATUS',
 ];
 public $wip_resource_transaction_id;
 public $wip_wo_header_id;
 public $wip_wo_routing_line_id;
 public $wip_wo_routing_detail_id;
 public $org_id;
 public $transaction_type;
 public $transaction_date;
 public $transaction_quantity;
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
 public $department_id;
 public $wo_number;
 public $item_number;
 public $item_id;
 public $routing_sequence;
 public $gl_journal_header_id;

 Public static function wip_transactions() {
	$option_header = option_header::find_by_name('WIP_TRANSACTIONS');
	$wip_transactions = option_line::find_by_option_id($option_header->option_header_id);
	return $wip_transactions;
 }

 private function _save_journal_header() {
	$inv = new inventory();
	$inv_i = $inv->findRelatedDetail_ByOrgId($this->org_id);
	$gled = new gl_ledger();
	$gled->findBy_id($inv_i->ledger_id);
	$gp = new gl_period();
	$current_open_period = $gp->current_open_period($inv_i->ledger_id);
	$gjh = new gl_journal_header;
	$gjh->ledger_id = $inv_i->ledger_id;
	$gjh->status = 'ENTERED';
	$gjh->currency = $gled->currency_code;
	$gjh->period_id = $current_open_period->gl_period_id;
	$gjh->journal_source = self::$module;
	$gjh->journal_category = self::$gl_journal_category;
	$gjh->reference_type = 'table';
	$gjh->reference_key_name = self::$table_name;
	$gjh->reference_key_value = $this->wip_move_transaction_id;
	$gjh->journal_name = $gjh->journal_category . '-' . $gjh->reference_key_value;
	$gjh->description = $gjh->journal_name . '-' . current_time();
	$gjh->balance_type = 'A';
	$gjh->audit_trial();
	$gjh->save();
	$this->gl_journal_header_id = $gjh->gl_journal_header_id;
	echo "<br> The New Journal Header Id is " . $this->gl_journal_header_id;
	return $gjh->gl_journal_header_id;
 }

 private function _save_journal_lines($data_a) {
	global $dbc;
	$new_gjl = new gl_journal_line();
	$new_gjl->gl_journal_header_id = $this->gl_journal_header_id;
	$new_gjl->line_num = $data_a['line_number'];
	$new_gjl->status = 'U';
	$new_gjl->code_combination_id = $data_a['account_id'];
	if (($data_a['dr_cr']) == 'dr') {
	 $new_gjl->total_dr = $data_a['amount'];
	 $new_gjl->total_ac_dr = $data_a['amount'];
	} else {
	 $new_gjl->total_cr = $data_a['amount'];
	 $new_gjl->total_ac_cr = $data_a['amount'];
	}
	$new_gjl->description = 'WIP Move Transaction Id ' . $this->wip_move_transaction_id;
	$new_gjl->reference_type = 'table';
	$new_gjl->reference_key_name = 'wip_move_transaction';
	$new_gjl->reference_key_value = $this->wip_move_transaction_id;
	$new_gjl->audit_trial();
	$new_gjl->save();
	$dbc->confirm();
 }

 public function _after_save() {
	global $db;
	//Insert in WIP WO BOM - item issues for operational pull
	if ((!empty($this->wip_resource_transaction_id)) && (!(empty($this->wip_wo_routing_detail_id))) && (!(empty($this->transaction_quantity)))) {
	 $wip_wo_routing_detail = new wip_wo_routing_detail();
	 $wip_wo_routing_detail_i = $wip_wo_routing_detail->findBy_id($this->wip_wo_routing_detail_id);
	 if ($wip_wo_routing_detail->charge_type != 'WIP_MOVE') {
		return 10;
	 }
	 $wip_wo_routing_detail->wip_wo_routing_detail_id = $wip_wo_routing_detail_i->wip_wo_routing_detail_id;
	 $wip_wo_routing_detail->applied_quantity = $wip_wo_routing_detail_i->applied_quantity + $this->transaction_quantity;
	 try {
		$wip_wo_routing_detail->audit_trial();
		$wip_wo_routing_detail->save();
		$resource = new bom_resource();
		$resource->findBy_id($wip_wo_routing_detail->resource_id);
		$total_amount = $resource->rate_reference_id * $this->transaction_quantity;

		if (!empty($total_amount)) {
		 $journal_line_a = [];
		 $journal_line = [];
		 $this->_save_journal_header();
		 $line_number = 1;
		 $woh = new wip_wo_header();
		 $woh->findBy_id($this->wip_wo_header_id);
		 $wip_accounting_group = new wip_accounting_group();
		 $wip_accounting_group->findBy_id($woh->wip_accounting_group_id);
		 $journal_line['line_number'] = $line_number;
		 $journal_line['amount'] = $total_amount;
		 $journal_line['account_id'] = $wip_accounting_group->resource_ac_id;
		 $journal_line['dr_cr'] = 'dr';
		 array_push($journal_line_a, $journal_line);
		 $line_number++;
		 $journal_line['line_number'] = $line_number;
		 $journal_line['amount'] = $total_amount;
		 $journal_line['account_id'] = $resource->absorption_ac_id;
		 $journal_line['dr_cr'] = 'cr';
		 array_push($journal_line_a, $journal_line);
		 $this->_save_journal_lines($journal_line_a);
		}
		echo "<br> The resource quantity is sucessfully applied ";
	 } catch (Exception $e) {
		echo "<br> Resource quantity application " . $e->getMessage();
	 }
	}
 }

 public function save() {
	$primary_column = static::$primary_column;
	if (empty($this->$primary_column)) {
	 $this->create();
	} else {
	 echo '<div class="message"> You are not allowed to update a completed move transaction!</div>';
	}
	return $this->msg;
 }

 public function _before_showing() {
	
 }

 public function _before_save() {
	
 }

}

//end of resource class
?>



