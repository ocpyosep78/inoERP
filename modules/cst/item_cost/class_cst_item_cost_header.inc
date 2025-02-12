<?php

class cst_item_cost_header extends dbObject {

 public static $table_name = "cst_item_cost_header";
 public static $dependent_classes = ['cst_item_cost_line'];
 public static $primary_column = "cst_item_cost_header_id";
 public static $key_column = 'item_id';
 public static $module = "cst"; //same as gl_journal_source
// public static $js_fileName = 'modules/cst/item_cost/item_cost.js';
 public static $gl_journal_category = "CST_ADJUSTMENT";
 public $field_a = [
		 'cst_item_cost_header_id',
		 'org_id',
		 'bom_cost_type',
		 'item_id',
		 'based_on_rollup_cb',
		 'include_in_rollup_cb',
		 'sales_price',
		 'purchase_price',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
 public $initial_search = [
		 'item_id',
		 'based_on_rollup_cb',
		 'include_in_rollup_cb',
 ];
 public $column = [
		 'cst_item_cost_header_id',
		 'org_id',
		 'bom_cost_type',
		 'item_id',
		 'based_on_rollup_cb',
		 'include_in_rollup_cb',
		 'sales_price',
		 'purchase_price',
 ];
 public $requiredField = [
		 'org_id',
		 'bom_cost_type',
		 'item_id',
 ];
 public $checkbox = [
		 "based_on_rollup_cb",
		 'include_in_rollup_cb'
 ];
 public $fields_inForm_notInDataBase = [
		 "item_number",
		 "item_description",
		 "uom",
		 'action'
 ];
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
//		 '_view_action_meassge' => 'View',
//		 '_extra_path' => '',
 ];
 public $pageTitle = " CST - Item Cost  "; //page Title
 public $option_lists = [
//		 'receipt_types' => 'AR_RECEIPT_TYPE',
//		 'po_status' => 'PO_STATUS',
 ];
 public $search_functions = [
		 'Cost Type' => 'search_bom_cost_type',
		 'Item From' => 'search_item_number_from',
		 'Item To' => 'search_item_number_to',
		 'Organization' => 'search_org_name',
 ];
 public $prg_standard_cost_update_parameters = [
		 'Adjustment Ac' => 'adjustment_ac_id',
		 'Organization' => 'search_org_name',
		 'Cost Type' => 'search_bom_cost_type',
		 'Item Number From' => 'search_item_number_from',
		 'Item Number To' => 'search_item_number_to',
		 'Item Id From' => 'search_item_id_from',
		 'Item Id To' => 'search_item_id_to'
 ];
 public $prg_cost_rollup_parameters = [
		 'Organization' => 'search_org_name',
		 'Cost Type' => 'search_bom_cost_type',
		 'Item Number From' => 'search_item_number_from',
		 'Item Number To' => 'search_item_number_to',
		 'Item Id From' => 'search_item_id_from',
		 'Item Id To' => 'search_item_id_to'
 ];
 public $prg_cost_rollup_details = [
		 'name' => 'Cost Roll Up',
		 'description' => 'Roll up cost for pending or user defiled cost types',
 ];
 public $prg_standard_cost_update_details = [
		 'name' => 'Standard Cost Update',
		 'description' => 'Update Frozen Cost from a different cost type',
		 'Item To' => 'search_item_number_to'
 ];
 public $cst_item_cost_header_id;
 public $bom_cost_type;
 public $org_id;
 public $item_id;
 public $based_on_rollup_cb;
 public $include_in_rollup_cb;
 public $sales_price;
 public $purchase_price;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $item_number;
 public $item_description;
 public $uom;
 public $action;
 public $message = '';
 public $parameters;
 public $adjustment_ac_id;
 public $gl_journal_header_id;

 public function __construct() {
	parent::__construct();
	$this->prg_cost_rollup_parameters = $this->prg_standard_cost_update_parameters;
 }

 Public static function transaction_action() {
	$option_header = option_header::find_by_name('CST_COST_ACTION');
	$lines = option_line::find_by_option_id($option_header->option_header_id);
	return $lines;
 }

 public function findBy_ItemId_CostType() {
	$sql = " SELECT * FROM  ";
	$sql .= self::$table_name;
	$sql .= " WHERE bom_cost_type =:bom_cost_type AND item_id = :item_id ";
	$sql .= " LIMIT 1 ";

	$param_a = ['bom_cost_type', 'item_id'];
	$value_a = ['bom_cost_type' => $this->bom_cost_type, 'item_id' => $this->item_id];
	$result = $this->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 public function find_frozen_cost() {
	$this->bom_cost_type = 'FROZEN';
	return $this->findBy_ItemId_CostType();
 }

 public function _before_save() {
	/* Check the cost type - If its FROZEN then show error message */
	if ((isset($this->bom_cost_type)) && ($this->bom_cost_type == 'FROZEN')) {
	 echo " You can't create/update item cost for frozen cost type. <br> Create Item cost in pending(or any user defined cost type)and then run standard cost update. ";
	 return -99;
	}
	if ((!empty($this->cst_item_cost_header_id)) && ($this->action == 'COST_UPDATE') && (($this->bom_cost_type != 'FROZEN'))) {
	 $this->_update_standard_cost();
	 return 10;
	}
	if ((!empty($this->cst_item_cost_header_id)) && ($this->action == 'COST_ROLLUP') && (($this->bom_cost_type != 'FROZEN'))) {
	 $this->cost_rollup($this->item_id, $this->bom_cost_type);
	 return 10;
	}

	if ((!empty($this->cst_item_cost_header_id)) && ($this->action === 'create_accounting')) {
	 $asis_data = $this->findBy_id($this->cst_item_cost_header_id);
	 foreach ($asis_data as $key => $value) {
		$this->$key = $value;
	 }
	 //if journal header id excists then save journal lines only else first header & then lines
	 if (empty($this->gl_journal_header_id)) {
		try {
		 $this->_save_journal_header();
		 try {
			echo "<br>Accounting records are sucessfully created " . $this->gl_journal_header_id;
			$this->_update_journalHeaderId();
		 } catch (Exception $e) {
			echo "<br>Updating gl journal header id failed" . $e->getMessage();
		 }
		} catch (Exception $e) {
		 echo "Create accounting failed" . $e->getMessage();
		}
	 }
	 if (!empty($this->gl_journal_header_id)) {
		//check the status is not updated and then save/update journal lines
		$gjh = new gl_journal_header();
		$gjh_i = $gjh->findBy_id($this->gl_journal_header_id);
		if ($gjh_i->status == 'ENTERED') {
		 $this->_save_journal_lines();
		} else {
		 echo "<br> The Journal Header \" $gjh_i->journal_name \" (id : $this->gl_journal_header_id ) is not in Entered Status."
		 . "<br>From Subledger, You can only update Jouranls in Entered Status";
		 return;
		}
	 }

	 return 10;
	}

	if ((!empty($this->cst_item_cost_header_id)) && ($this->action == 'CANCEL')) {
	 $this->_cancel_transaction();
	 return 10;
	}
 }

 public function _after_save() {
	
 }

 private function _update_standard_cost($parameters) {
	global $dbc;
	/*
	 * 1. First check if frozen cost exists for the item_id 
	 * 2. Copy the header and create/update frozen
	 * 3. Copy all the line and update with the new frozen cost header id
	 * $this has 	 item_id & bom_cost_type (Pending), adjustment_Ac as entered parameters & cst_item_cost_header_id if exists
	 */
	$old_records_a = [];
	$message = "<br><br>Starting to update standard header";
	$this->findBy_id($this->cst_item_cost_header_id);
	$ich_f = new cst_item_cost_header();
	foreach ($this->field_a as $key => $value) {
	 $ich_f->$value = $this->$value;
	}
	$existing_fozen_cost = $this->find_frozen_cost();
	if (!empty($existing_fozen_cost)) {
	 $ich_f->cst_item_cost_header_id = $existing_fozen_cost->cst_item_cost_header_id;
	 //copy all the lines to cst_item_cost_line_pre	
	 $icl_existing = new cst_item_cost_line();
	 $icl_existing_i = $icl_existing->findBy_parentId($ich_f->cst_item_cost_header_id);
	 foreach ($icl_existing_i as $existing_cost_lines) {
		$iclp = new cst_item_cost_line_pre();
		$icl = new cst_item_cost_line();
		foreach ($icl->field_a as $key2 => $value2) {
		 $iclp->$value2 = $existing_cost_lines->$value2;
		}
		//check if record all ready exoists
		$iclp_i = $iclp->findBy_lineId();
		if (!empty($iclp_i)) {
		 $iclp->cst_item_cost_line_pre_id = $iclp_i->cst_item_cost_line_pre_id;
		}
		array_push($old_records_a, $existing_cost_lines);
		$iclp->save();
	 }
	} else {
	 $ich_f->cst_item_cost_header_id = null;
	}
	$ich_f->bom_cost_type = 'FROZEN';
	$ich_f->audit_trial();
	try {
	 $ich_f->save();
	 if (!empty($ich_f->cst_item_cost_header_id)) {
		$message .=" <br>Item cost head is sucessfully updated for cst_item_cost_header_id " . $ich_f->cst_item_cost_header_id;
		//save cost line
		$message .= $this->_update_standard_cost_lines($ich_f, $old_records_a, $parameters);
		//update the WIP & Onhand Value Balances
	 }
	} catch (Excption $e) {
	 $dbc->rollback = true;
	 $message .= "<br>Saving frozen cost header failed!" . $e->getMessage();
	}
	return $message;
 }

 private function _update_standard_cost_lines(&$header_obj, $old_records_a, $parameters) {
	$new_records_a = [];
	$icl = new cst_item_cost_line();
	$all_cost_lines = $icl->findBy_parentId($this->cst_item_cost_header_id);
	if (empty($all_cost_lines)) {
	 $message = "<br/>Leaving Standard cost update as no cost line exists";
	 return;
	}
	$message = "<br/>Starting to update standard cost lines";
	foreach ($all_cost_lines as $cost_line) {
	 foreach ($icl->field_a as $key => $value) {
		$icl->$value = $cost_line->$value;
	 }
	 //check if line already exists by searching cost_element_id and header_id
	 $icl->cst_item_cost_header_id = $header_obj->cst_item_cost_header_id;
	 $icl->cost_element_id = $cost_line->cost_element_id;
	 $icl->cost_element_type = $cost_line->cost_element_type;
	 $existing_line = $icl->findBy_headerId_elementId();
	 if (!empty($existing_line)) {
		$icl->cst_item_cost_line_id = $existing_line->cst_item_cost_line_id;
	 } else {
		$icl->cst_item_cost_line_id = null;
	 }
	 try {
		$icl->audit_trial();
		array_push($new_records_a, $cost_line);
		$icl->save();
		$message .= "<br>Frozen cost line is sucessfully saved!";
	 } catch (Exception $e) {
		$message .= "<br>Saving frozen cost line failed!" . $e->getMessage();
	 }
	}
	try {
	 $this->_update_onhandValue_after_costUpdate($old_records_a, $new_records_a, $parameters);
	} catch (Exception $e) {
	 $message = "<br/>Onhand update failed! @ cst_item_cost_header " . __LINE__ . '<br>' . $e->getMessage();
	}
	return $message;
 }

 private function _update_onhandValue($old_records_a, $new_records_a, $onhand_record, $parameters) {
	$element_array = ['mat', 'moh', 'oh', 'res', 'osp'];
	foreach ($element_array as $key => $value) {
	 $data_o = $value . '_o';
	 $data_n = $value . '_n';
	 $$data_o = 0;
	 $$data_n = 0;
	}
	foreach ($old_records_a as $old_record) {
	 $mat_o += array_search('MAT', ((array) $old_record)) ? $old_record->amount : 0;
	 $moh_o += array_search('MOH', ((array) $old_record)) ? $old_record->amount : 0;
	 $oh_o += array_search('OH', ((array) $old_record)) ? $old_record->amount : 0;
	 $res_o += array_search('RES', ((array) $old_record)) ? $old_record->amount : 0;
	 $osp_o += array_search('OSP', ((array) $old_record)) ? $old_record->amount : 0;
	}
	foreach ($new_records_a as $new_records) {
	 $mat_n += array_search('MAT', ((array) $new_records)) ? $new_records->amount : 0;
	 $moh_n += array_search('MOH', ((array) $new_records)) ? $new_records->amount : 0;
	 $oh_n += array_search('OH', ((array) $new_records)) ? $new_records->amount : 0;
	 $res_n += array_search('RES', ((array) $new_records)) ? $new_records->amount : 0;
	 $osp_n += array_search('OSP', ((array) $new_records)) ? $new_records->amount : 0;
	}

	/* if mat_n - mat_o is neagtive cr the inventory & debit adjustment ac	
	  if mat_n - mat_o is positive dr the inventory & credit adjustment ac */
	$mat_d = $mat_n - $mat_o;
	$moh_d = $moh_n - $moh_o;
	$oh_d = $oh_n - $oh_o;
	$res_d = $res_n - $res_o;
	$osp_d = $osp_n - $osp_o;
	$adjustment_amount = 0;
	if ((!empty($mat_d)) || (!empty($moh_d)) || (!empty($oh_d)) || (!empty($res_d)) || (!empty($osp_d))) {
	 $line_data_a = [];
	 $line_number = 1;
	 $this->_save_journal_header();
	 $line_data_a['gl_journal_header_id'] = $this->gl_journal_header_id;
	} else {
	 return 10;
	}

	$subinv = new subinventory();
	$subinv_i = $subinv->findBy_id($onhand_record->subinventory_id);

	foreach ($element_array as $key => $value) {
	 $data_d = $value . '_d';
	 if (!empty($$data_d)) {
		//Dr inventory & Credit Adjustment
		$adjustment_amount += $$data_d;
		$line_data_a['line_number'] = $line_number;
		$line_number++;
		switch ($data_d) {
		 case 'mat_d':
			$line_data_a['ccid'] = $subinv_i->material_ac_id;
			break;
		 case 'moh_d':
			$line_data_a['ccid'] = $subinv_i->material_oh_ac_id;
			break;
		 case 'oh_d':
			$line_data_a['ccid'] = $subinv_i->overhead_ac_id;
			break;
		 case 'res_d':
			$line_data_a['ccid'] = $subinv_i->resource_ac_id;
			break;
		 case 'osp_d':
			$line_data_a['ccid'] = $subinv_i->osp_ac_id;
			break;
		 default :
			break;
		}

		$line_data_a['amount'] = abs($$data_d);
		$line_data_a['cst_item_cost_header'] = $old_records_a[0]->cst_item_cost_header_id;
		if ($$data_d > 0) {
		 $line_data_a['dr_cr'] = 'dr';
		} else {
		 $line_data_a['dr_cr'] = 'cr';
		}
		$this->_save_journal_lines($line_data_a);
	 }
	}

	if (!empty($parameters['adjustment_ac_id'][0])) {
	 $adjustment_ac = $parameters['adjustment_ac_id'][0];
	 $coa = new coa_combination();
	 $coa_i = $coa->findBy_exactCombination($adjustment_ac);
	 if (!empty($coa_i)) {
		$adjustment_ac_id = $coa_i->coa_combination_id;
	 }
	}
	if (!empty($adjustment_amount)) {
	 //Dr or Cr Adjustment Amount
	 $line_data_a['line_number'] = 9999;
	 $line_data_a['ccid'] = $adjustment_ac_id;
	 $line_data_a['amount'] = abs($adjustment_amount);
	 $line_data_a['cst_item_cost_header'] = $old_records_a[0]->cst_item_cost_header_id;
	 if ($adjustment_amount < 0) {
		$line_data_a['dr_cr'] = 'dr';
	 } else {
		$line_data_a['dr_cr'] = 'cr';
	 }
	 $this->_save_journal_lines($line_data_a);
	}
 }

 private function _update_onhandValue_after_costUpdate($old_records_a, $new_records_a, $parameters) {
	$onhand = new onhand();
	$onhand_i = $onhand->findOnhand_byItemId($this->item_id);
	if (empty($onhand_i)) {
	 return 10;
	} else {
	 foreach ($onhand_i as $onhand_records) {
		$this->_update_onhandValue($old_records_a, $new_records_a, $onhand_records, $parameters);
	 }
	}
 }

 public function prg_standard_cost_update($seralized_parameters) {
	$parameters = unserialize($seralized_parameters);
	$this->message .= '<br> Start of standard cost update program';
	if (!empty($parameters['adjustment_ac_id'][0])) {
	 $adjustment_ac = $parameters['adjustment_ac_id'][0];
	 $coa = new coa_combination();
	 $coa_i = $coa->findBy_exactCombination($adjustment_ac);
	 $this->message .= '<br> Entered Adjustment AC is : ' . $adjustment_ac;
	 if (!empty($coa_i)) {
		$this->adjustment_ac_id = $coa_i->coa_combination_id;
	 } else {
		$this->message .= '<br> Error! : No Adjustment AC Id found @ cst_item_cost_header ' . __LINE__;
		return $this->message;
	 }
	} else {
	 $this->message .= '<br> Error! : No Adjustment AC found @ cst_item_cost_header ' . __LINE__;
	 return $this->message;
	}

	if (!empty($parameters['org_id'][0])) {
	 $this->org_id = $org_id = $parameters['org_id'][0];
	 $this->message .= '<br> Entered Org Id is : ' . $org_id;
	} else {
	 $this->message .= '<br> Error! : No org id found @ cst_item_cost_header ' . __LINE__;
	 return $this->message;
	}

	if (!empty($parameters['bom_cost_type'][0])) {
	 $bom_cost_type = $parameters['bom_cost_type'][0];
	 $this->message .= '<br> Entered BOM Cost Type is : ' . $bom_cost_type;
	} else {
	 $this->message .= '<br> Error! : No BOM Cost Type is found @ cst_item_cost_header ' . __LINE__;
	 return $this->message;
	}

	if (!empty($parameters['item_id'][0])) {
	 $this->message .= "<br>Using Standard cost update by Item Id ";
	 $ich = new cst_item_cost_header();
	 $ich->item_id = $parameters['item_id'][0];
	 $ich->bom_cost_type = $bom_cost_type;
	 $ich_i = $ich->findBy_ItemId_CostType();
	 if (!empty($ich_i)) {
		$ich->cst_item_cost_header_id = $ich_i->cst_item_cost_header_id;
		try {
		 $this->message .= $ich->_update_standard_cost($parameters);
		 $this->message .= "<br/>Standard cost update is sucessfully updated for item_id - " . $ich->item_id .
						 ' bom_cost_type : ' . $ich->bom_cost_type;
		} catch (Exception $e) {
		 $this->message .= "<br/>Standard cost update fialed for Item id " . $ich->item_id . $e->getMessage();
		}
	 } else {
		$this->message .= "<br/>Leaving Standard cost update as no cost exists item_id - " . $ich->item_id .
						' bom_cost_type : ' . $ich->bom_cost_type;
	 }
	 return $this->message;
	}

	if (!empty($parameters['from_item_id'][0])) {
	 $this->message .= "<br>Using Standard cost update by Item Id Range ";
	 $from_item_id = $parameters['from_item_id'][0];
	 if (!empty($parameters['to_item_id'][0])) {
		$to_item_id = $parameters['to_item_id'][0];
	 } else {
		$to_item_id = $from_item_id;
	 }
	 $item = new item();
	 $item_range = $item->findBy_itemIdRange($from_item_id, $to_item_id);
	 foreach ($item_range as $items) {
		$ich = new cst_item_cost_header();
		$ich->item_id = $items->item_id;
		$ich->bom_cost_type = $bom_cost_type;
		$ich_i = $ich->findBy_ItemId_CostType();
		if (!empty($ich_i)) {
		 $ich->cst_item_cost_header_id = $ich_i->cst_item_cost_header_id;
		 try {
			$this->message .= "<br> Going for standard cost update for item header... ";
			$this->message .= $ich->_update_standard_cost($parameters);
			$this->message .= "<br> Standard cost update is sucessfully updated for item_id - " . $ich->item_id .
							' bom_cost_type : ' . $ich->bom_cost_type;
		 } catch (Exception $e) {
			$this->message .= "<br/>Standard cost update fialed for Item id " . $ich->item_id . $e->getMessage();
		 }
		} else {
		 $this->message .= "<br/>Leaving Standard cost update as no cost exists item_id - " . $ich->item_id .
						 ' bom_cost_type : ' . $ich->bom_cost_type;
		}
	 }
	 return $this->message;
	}

	if (!empty($parameters['from_item_number'][0])) {
	 $this->message .= "<br>Using Standard cost update by Item Number Range ";
	 $from_item_number = $parameters['from_item_number'][0];
	 if (!empty($parameters['to_item_number'][0])) {
		$to_item_number = $parameters['to_item_number'][0];
	 } else {
		$to_item_number = $from_item_number;
	 }
	 $item = new item();
	 $item_range = $item->findBy_itemNumberRange_OrgId($from_item_number, $to_item_number, $org_id);

	 foreach ($item_range as $items) {
		$ich = new cst_item_cost_header();
		$ich->item_id = $items->item_id;
		$ich->bom_cost_type = $bom_cost_type;
		$ich_i = $ich->findBy_ItemId_CostType();
		if (!empty($ich_i)) {
		 $ich->cst_item_cost_header_id = $ich_i->cst_item_cost_header_id;
		 try {
			$ich->_update_standard_cost($parameters);
		 } catch (Exception $e) {
			$this->message .= "<br/>Standard cost update fialed for Item id " . $ich->item_id . $e->getMessage();
		 }
		} else {
		 $this->message .= "<br/>Leaving Standard cost update as no cost exists";
		}
	 }
	 return $this->message;
	}
 }

 private function _add_update_cost_lines($header_obj, $cost_lines) {
	$icl = new cst_item_cost_line();
	$icl_i = $icl->findBy_parentId($header_obj->cst_item_cost_header_id);
	if (empty($icl_i)) {
	 foreach ($cost_lines as $new_lines) {
		$icl->cst_item_cost_header_id = $header_obj->cst_item_cost_header_id;
		$icl->cost_element_type = $new_lines->cost_element_type;
		$icl->cost_element_id = $new_lines->cost_element_id;
		$icl->amount = $new_lines->amount;
		$icl->cost_basis = $new_lines->cost_basis;
		$icl->cst_item_cost_line_id = null;
		$icl->audit_trial();
		$icl->save();
	 }
	} else {
	 foreach ($cost_lines as $new_lines) {
		$icl->cst_item_cost_header_id = $header_obj->cst_item_cost_header_id;
		$icl->cost_element_type = $new_lines->cost_element_type;
		$icl->cost_element_id = $new_lines->cost_element_id;
		$icl->amount = $new_lines->amount;
		$icl->cost_basis = $new_lines->cost_basis;
		$existing_line = $icl->findBy_headerId_elementId();
		if (!empty($existing_line)) {
		 $icl->cst_item_cost_line_id = $existing_line->cst_item_cost_line_id;
		}
		$icl->audit_trial();
		$icl->save();
	 }
	}
 }

 private function _update_linesum_by_resource_overhead(&$linesum, $routing_line_i, $bom_cost_type) {
	foreach ($routing_line_i as $routing_line) {
	 $routing_detail = new bom_routing_detail();
	 $routing_detail_i = $routing_detail->findBy_parentId($routing_line->bom_routing_line_id);
	 foreach ($routing_detail_i as $routing_detail) {

		if (!empty($routing_detail->resource_id)) {
		 $linesum_newdata = new stdClass();
		 $resource_cost = new bom_resource_cost();
		 $resource_cost->bom_resource_id = $routing_detail->resource_id;
		 $resource_cost->bom_cost_type = $bom_cost_type;
		 $resource_cost_i = $resource_cost->findBy_resourceId_bomCostType();
		 $linesum_newdata->amount = $resource_cost_i->resource_rate * $routing_detail->resource_usage;
		 $linesum_newdata->cost_element_type = 'RES';
		 $linesum_newdata->cost_element_id = $routing_detail->resource_id;
		 $linesum_newdata->cost_basis = $routing_detail->charge_basis;
		 array_push($linesum, $linesum_newdata);

		 //overhead
		 $boh = new bom_overhead_v();
		 $boh->resource_id = $routing_detail->resource_id;
		 $boh->resource_bom_cost_type = $bom_cost_type;
		 $boh_i = $boh->findBy_resourceId_bomCostType();
		 if (!empty($boh_i)) {
			foreach ($boh_i as $overhead) {
			 $linesum_newOHdata = new stdClass();
			 $linesum_newOHdata->amount = $overhead->rate * $linesum_newdata->amount;
			 $linesum_newOHdata->cost_element_type = 'OH';
			 $linesum_newOHdata->cost_element_id = $overhead->bom_overhead_id;
			 $linesum_newOHdata->cost_basis = $overhead->default_basis;
			 array_push($linesum, $linesum_newOHdata);
			}
		 }
		}
	 }
	}
 }

 private function _cost_rollup_cost_lines($header_obj) {
	global $dbc;
	$line_sums = [];
	$boh = new bom_header();
	$boh->item_id = $header_obj->item_id;
	$boh_i = $boh->findBy_itemId();
	if (empty($boh_i)) {
	 return;
	}
	$roh = new bom_routing_header();
	$roh->item_id = $header_obj->item_id;
	$roh_i = $roh->findBy_itemId();
	$rol = new bom_routing_line();
	$rol_i = $rol->findBy_parentId($roh_i->bom_routing_header_id);
	$bol = new bom_line();
	$bol_i = $bol->findBy_parentId($boh_i->bom_header_id);
	if (empty($bol_i)) {
	 return;
	}
	$ich = new cst_item_cost_header();
	$icl = new cst_item_cost_line();

	foreach ($bol_i as $bom_lines) {
	 $ich->item_id = $bom_lines->component_item_id;
	 $ich->bom_cost_type = $header_obj->bom_cost_type;
	 $ich_i = $ich->findBy_ItemId_CostType();
	 if (!empty($ich_i)) {
		$icl_i = $icl->findBy_parentId($ich_i->cst_item_cost_header_id);
		if (!empty($icl_i)) {
		 foreach ($icl_i as $cost_lines) {
			$cost_lines_a = [];
			$cost_lines_a['cost_element_type'] = $cost_lines->cost_element_type;
			$cost_lines_a['cost_element_id'] = $cost_lines->cost_element_id;
			$cost_lines_a['cost_basis'] = $cost_lines->cost_basis;
			if (!empty($line_sums)) {
			 $add_a_newline = true;
			 foreach ($line_sums as &$line_sums_lines) {
				if (count(array_intersect((array) $line_sums_lines, $cost_lines_a)) == 3) {
				 $line_sums_lines->amount += $cost_lines->amount;
				 $add_a_newline = false;
				 break;
				}
			 }
			 if ($add_a_newline) {
				array_push($line_sums, $cost_lines);
			 }
			} else {
			 array_push($line_sums, $cost_lines);
			}
		 }
		}
	 }
	}
	$this->_update_linesum_by_resource_overhead($line_sums, $rol_i, $header_obj->bom_cost_type);
	pa($line_sums);
	$this->_add_update_cost_lines($header_obj, $line_sums);
 }

 private function _cost_rollup_forItem($item_id, $cost_type) {
	$ich = new cst_item_cost_header();
	$ich->item_id = $item_id;
	$ich->bom_cost_type = $cost_type;
	$existing_cost_type = $ich->findBy_ItemId_CostType();
	if (!empty($existing_cost_type)) {
	 $ich->cst_item_cost_header_id = $existing_cost_type->cst_item_cost_header_id;
	} else {
	 $ich->cst_item_cost_header_id = null;
	 $item = new item();
	 $item_i = $item->findBy_id($item_id);
	 $ich->org_id = $item_i->org_id;
	}
	$ich->audit_trial();
	try {
	 $ich->save();
	 if (!empty($ich->cst_item_cost_header_id)) {
		$this->message .=" <br>Item cost heade is sucessfully updated for cst_item_cost_header_id " . $ich->cst_item_cost_header_id;
		//save cost line
		$this->_cost_rollup_cost_lines($ich);
	 }
	} catch (Excption $e) {
	 $this->message .= "<br>Saving frozen cost header failed!" . $e->getMessage();
	}
 }

 public function cost_rollup($item_id, $cost_type) {
	global $dbc;
	/*
	 * 1. First explode the bom and add low level code 
	 * 2. Roll up the cost from the lowest level - 
	 * 2.1 _cost_rollup_forItem - Cost Roll up for each Item
	 *    2.2 _cost_rollup_cost_lines - Cost roll up for each line
	 *    2.3 _add_update_cost_lines - Add/Updates the cost lines
	 */
	$boh = new bom_header();
	$exploded_bom = $boh->BOM_Explosion($item_id);
	$exploded_bom_rev = array_reverse($exploded_bom, true);
	$item = new item();

	foreach ($exploded_bom_rev as $level_items) {
	 foreach ($level_items as $item_key => $item_id) {
		$item->findBy_id($item_id);
		if ($item->make_buy == 'Make') {
		 try {
			$this->_cost_rollup_forItem($item->item_id, $cost_type);
			$this->message .= "Cost roll up is sucessfully completed for Item Number : $item->item_number & Cost Type : $cost_type";
		 } catch (Exception $e) {
			$this->message .= "Cost roll up failed for Item Number : $item->item_number & Cost Type : $cost_type. Error @ " . __LINE__
							. '<br>' . $e->getMessage();
		 }
		}
	 }
	}

	execution_time();
 }

 public function prg_cost_rollup($seralized_parameters) {
	$parameters = unserialize($seralized_parameters);
	$this->message = '<br> Start of cost roll up program';

	if (!empty($parameters['org_id'][0])) {
	 $org_id = $parameters['org_id'][0];
	 $this->message .= '<br> Entered Org Id is : ' . $org_id;
	} else {
	 $this->message .= '<br> Error! : No org id found @ cst_item_cost_header ' . __LINE__;
	 return $this->message;
	}

	if (!empty($parameters['bom_cost_type'][0])) {
	 $bom_cost_type = $parameters['bom_cost_type'][0];
	 $this->message .= '<br> Entered BOM Cost Type is : ' . $bom_cost_type;
	} else {
	 $this->message .= '<br> Error! : No BOM Cost Type is found @ cst_item_cost_header ' . __LINE__;
	 return $this->message;
	}

	if (isset($parameters['item_id'][0])) {
	 $this->message .= "<br/>Using Cost Roll Up by Item Id ";
	 $item_id = $parameters['item_id'][0];
	 try {
		$this->cost_rollup($item_id, $bom_cost_type);
		$this->message .= "<br/>Cost Roll Up is sucessfully updated for item_id - " . $item_id .
						' bom_cost_type : ' . $bom_cost_type;
	 } catch (Exception $e) {
		$this->message .= "<br/>Cost Roll Up fialed for Item id " . $item_id . $e->getMessage();
	 }

	 return $this->message;
	}

	if (isset($parameters['from_item_id'][0])) {
	 $this->message .= "<br/>Using Cost Roll Up by Item Id Range ";
	 $from_item_id = $parameters['from_item_id'][0];
	 if (!empty($parameters['to_item_id'][0])) {
		$to_item_id = $parameters['to_item_id'][0];
	 } else {
		$to_item_id = $from_item_id;
	 }
	 $item = new item();
	 $item_range = $item->findBy_itemIdRange($from_item_id, $to_item_id);
	 foreach ($item_range as $items) {
		try {
		 $this->cost_rollup($items->item_id, $bom_cost_type);
		 $this->message .= "<br/>Cost Roll Up is sucessfully updated for item_id - " . $items->item_id .
						 ' bom_cost_type : ' . $bom_cost_type;
		} catch (Exception $e) {
		 $this->message .= "<br/>Cost Roll Up fialed for Item id " . $items->item_id . $e->getMessage();
		}
	 }
	 return $this->message;
	}

	if (isset($parameters['from_item_number'][0])) {
	 $from_item_number = $parameters['from_item_number'][0];
	 if (!empty($parameters['to_item_number'][0])) {
		$to_item_number = $parameters['to_item_number'][0];
	 } else {
		$to_item_number = $from_item_number;
	 }
	 $item = new item();
	 $item_range = $item->findBy_itemNumberRange_OrgId($from_item_number, $to_item_number, $org_id);

	 foreach ($item_range as $items) {
		try {
		 $this->cost_rollup($items->item_id, $bom_cost_type);
		 $this->message .= "<br/>Cost Roll Up is sucessfully updated for item_id - " . $items->item_id .
						 ' bom_cost_type : ' . $bom_cost_type;
		} catch (Exception $e) {
		 $this->message .= "<br/>Cost Roll Up fialed for Item id " . $items->item_id . $e->getMessage();
		}
	 }
	 return $this->message;
	}
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
	$gjh->reference_key_value = $this->cst_item_cost_header_id . '-' . rand() . '-' . current_time();
	$gjh->journal_name = $gjh->journal_category . '-' . $this->cst_item_cost_header_id;
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
	$new_gjl->gl_journal_header_id = $data_a['gl_journal_header_id'];
	$new_gjl->line_num = $data_a['line_number'];
	$new_gjl->status = 'U';
	$new_gjl->code_combination_id = $data_a['ccid'];
	if (($data_a['dr_cr']) == 'dr') {
	 $new_gjl->total_dr = $data_a['amount'];
	 $new_gjl->total_ac_dr = $data_a['amount'];
	} else {
	 $new_gjl->total_cr = $data_a['amount'];
	 $new_gjl->total_ac_cr = $data_a['amount'];
	}
	$new_gjl->description = 'Cost Adjustment for Item Id' . $this->item_id;
	$new_gjl->reference_type = 'table';
	$new_gjl->reference_key_name = 'cst_item_cost_header';
	$new_gjl->reference_key_value = $data_a['cst_item_cost_header'];
	$new_gjl->audit_trial();
	$new_gjl->save();
	$dbc->confirm();
 }

 public function multi_select_input_fields() {
	$multi_select_input = [
	];
	return $multi_select_input;
 }

 public function multi_select_hidden_fields() {
	$multi_select_hidden = [
			'action_class_name',
			'mode',
			'action',
			'show_block',
			'program_name'
	];

	return $multi_select_hidden;
 }

}

//end of cst_item_cost_header class
?>