<?php

class ar_receipt_header extends dbObject {

 public static $table_name = "ar_receipt_header";
 public static $dependent_classes = ['ar_receipt_line'];
 public static $primary_column = "ar_receipt_header_id";
 public static $primary_column2 = "receipt_number";
 public static $key_column = 'ar_customer_id';
 public static $module = "ar"; //same as gl_journal_source
 public static $gl_journal_category = "AR_RECEIPTS";
 public static $system_info = [
		 'name' => 'AR Receipt',
		 'number' => '1303',
		 'description' => 'Receive money & apply to invoices',
		 'version' => '1.1.1.3',
		 'db_version' => '1001',
		 'mod_version' => '1.1.x-1.1',
		 'dependent_class' => array('ar_receipt_line', 'ar_receipt_interface'),
		 'primary_entity_cb' => '',
		 'module_name' => 'ar',
		 'weight' => 3
 ];
 public $checkbox = [
//		 "rev_enabled_cb"
 ];
 public $field_a = [
		 'ar_receipt_header_id',
		 'bu_org_id',
		 'receipt_type',
		 'receipt_number',
		 'ar_customer_id',
		 'ar_customer_site_id',
		 'from_bank_header_id',
		 'description',
		 'from_bank_line_id',
		 'to_bank_header_id',
		 'header_amount',
		 'currency',
		 'document_currency',
		 'to_bank_line_id',
		 'exchange_rate_type',
		 'exchange_rate',
		 'ef_id',
		 'document_date',
		 'document_number',
		 'ledger_id',
		 'period_id',
		 'pay_group',
		 'receipt_method',
		 'approval_status',
		 'receipt_status',
		 'reference_type',
		 'reference_key_name',
		 'reference_key_value',
		 'gl_journal_header_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
 public $initial_search = [
		 'ar_receipt_header_id',
		 'bu_org_id',
		 'receipt_type',
		 'ar_transaction_header_id',
		 'receipt_number',
		 'ar_customer_id',
		 'from_bank_header_id',
		 'description',
		 'document_date',
		 'document_number',
		 'ledger_id',
		 'period_id',
		 'pay_group',
		 'receipt_method',
		 'approval_status',
		 'receipt_status',
 ];
 public $column = [
		 'ar_receipt_header_id',
		 'bu_org_id',
		 'receipt_type',
		 'ar_transaction_header_id',
		 'receipt_number',
		 'ar_customer_id',
		 'from_bank_header_id',
		 'description',
		 'document_date',
		 'document_number',
		 'ledger_id',
		 'period_id',
		 'pay_group',
		 'gl_journal_header_id',
		 'receipt_method',
		 'approval_status',
		 'receipt_status',
		 'header_amount',
		 'currency',
		 'document_currency',
 ];
 public $requiredField = [
		 'bu_org_id',
		 'receipt_type',
		 'ar_customer_id',
		 'ar_customer_site_id',
		 'header_amount',
		 'currency',
		 'ledger_id',
		 'period_id'
 ];
 public $fields_inForm_notInDataBase = [
		 "supplier_name",
		 "customer_number",
		 "ar_customer_site_name",
		 'so_number',
		 'sd_so_header_id',
		 'action',
		 'receipt_action',
		 'ar_transaction_header_id'
 ];
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
//		 '_view_action_meassge' => 'View',
//		 '_extra_path' => '',
 ];
 public $pageTitle = " inoEMS - AR Receipt  "; //page Title
 public $option_lists = [
		 'receipt_types' => 'AR_RECEIPT_TYPE',
//		 'po_status' => 'PO_STATUS',
 ];
 public $ar_receipt_header_id;
 public $bu_org_id;
 public $ar_transaction_header_id;
 public $receipt_number;
 public $receipt_type;
 public $ar_customer_id;
 public $ar_customer_site_id;
 public $from_bank_header_id;
 public $description;
 public $from_bank_line_id;
 public $to_bank_header_id;
 public $header_amount;
 public $currency;
 public $document_currency;
 public $to_bank_line_id;
 public $exchange_rate_type;
 public $exchange_rate;
 public $ef_id;
 public $document_date;
 public $document_number;
 public $ledger_id;
 public $period_id;
 public $pay_group;
 public $receipt_method;
 public $approval_status;
 public $receipt_status;
 public $reference_type;
 public $reference_key_name;
 public $reference_key_value;
 public $gl_journal_header_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $customer_name;
 public $customer_number;
 public $ar_customer_site_name;
 public $so_number;
 public $sd_so_header_id;
 public $action;
 public $transaction_action;
 public $action_class_name;
 public $mode;
 public $multi_action_class_pc;
 public $multi_action_class_pc_value;

 public function __set($name, $value) {
	switch ($value) {
	 case $value:


		break;

	 default:
		$this->$name = $value;
		break;
	}
 }

 private function _update_journalHeaderId() {
	$arth = new ar_receipt_header();
	$arth->ar_receipt_header_id = $this->ar_receipt_header_id;
	$arth->gl_journal_header_id = $this->gl_journal_header_id;
	$arth->created_by = $this->created_by;
	$arth->creation_date = $this->creation_date;
	$arth->last_update_by = $this->last_update_by;
	$arth->last_update_date = $this->last_update_date;
	$arth->save();
 }

 public function _before_save() {
	if (($this->action == 'confirm_receipt')) {
	 $this->_confirm_receipt();
	 return 10;
	}
	if ((!empty($this->ar_receipt_header_id)) && ($this->action === 'create_accounting')) {
	 $asis_data = $this->findBy_id($this->ar_receipt_header_id);
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

	if ((!empty($this->ar_receipt_header_id)) && ($this->transaction_action == 'CANCEL')) {
	 $this->_cancel_transaction();
	 return 10;
	}
 }

 private function _confirm_receipt() {
	//find all interface lines group by customer name & invoice number
	//create interface headers for each customer
	echo "<br> in confirm receipt";
	$ar_int = new ar_receipt_interface();
	$all_lines = $ar_int->findAll_groupByCustomer();
	foreach ($all_lines as $ar_customer_site) {
	 //create a new receipt header
	 $arrh = new $this;
	 $total_header_amount = 0;
	 $ar_int_i = $ar_int->findBy_id($ar_customer_site[0]);
	 foreach ($arrh->field_a as $key => $value) {
		$arrh->$value = isset($ar_int_i->$value) ? $ar_int_i->$value : null;
	 }
	 $arrh->header_amount = $ar_int_i->amount;
	 try {
		$arrh->audit_trial();
		$arrh->save();
		$arrh->_after_save();
		foreach ($ar_customer_site as $site_key => $ar_int_id) {
		 $arrl = new ar_receipt_line();
		 $ar_int_j = $ar_int->findBy_id($ar_int_id);
		 foreach ($arrl->field_a as $arrl_key => $value) {
			$arrl->$value = isset($ar_int_j->$value) ? $ar_int_j->$value : null;
		 }
		 $arrl->ar_receipt_header_id = $arrh->ar_receipt_header_id;
		 $arrl->line_number = $site_key + 1;
		 $arrl->amount = $ar_int_j->amount;
		 $total_header_amount += $ar_int_j->amount;
		 try {
			$arrl->audit_trial();
			$arrl->save();
			$arrl->_after_save();
			$ar_int->ar_receipt_interface_id = $ar_int_id;
			try {
			 $ar_int->delete();
			} catch (Exception $e) {
			 echo "<br>Deleting Interface Line Failed" . $e->getMessage();
			}
		 } catch (Exception $e) {
			echo "<br>Creating receipt line failed" . $e->getMessage();
		 }
		}
		//update the header amount for receipt
		$arrh->header_amount = $total_header_amount;
		try {
		 $arrh->audit_trial();
		 $arrh->save();
		} catch (Exception $e) {
		 echo "<br>Updating receipt amount header failed" . $e->getMessage();
		}
	 } catch (Exception $e) {
		echo "<br>Creating receipt header failed" . $e->getMessage();
	 }
	}
 }

 public function _after_save() {
	global $db;
	if ((!empty($this->ar_receipt_header_id)) && empty($this->receipt_number)) {
	 $ar_receipt_header_id = $this->ar_receipt_header_id;
	 $bu_org_id = $this->bu_org_id;
	 $this->receipt_number = $bu_org_id . '-' . $ar_receipt_header_id;
	 echo '<br/> System created receipt number is ' . $this->receipt_number;
	 $this->save();
	}
 }

 private function _save_journal_header() {
	$gjh = new gl_journal_header;
	$gjh->ledger_id = $this->ledger_id;
	$gjh->status = 'ENTERED';
	$gjh->currency = $this->document_currency;
	$gjh->period_id = $this->period_id;
	$gjh->journal_source = self::$module;
	$gjh->journal_category = self::$gl_journal_category;
	$gjh->reference_type = 'table';
	$gjh->reference_key_name = self::$table_name;
	$gjh->reference_key_value = $this->ar_receipt_header_id;
	$gjh->journal_name = $gjh->journal_category . '-' . $gjh->reference_key_value;
	$gjh->description = $gjh->journal_name . '-' . current_time();
	$gjh->balance_type = 'A';
	$gjh->audit_trial();
	$gjh->save();
	$this->gl_journal_header_id = $gjh->gl_journal_header_id;
	echo "<br> The New Journal Header Id is " . $this->gl_journal_header_id;
 }

 private function _save_journal_lines() {

	//	Dr the cash account 
	$bu_org = new business();
	$bu_org->org_id = $this->bu_org_id;
	$bu_org_i = $bu_org->findBy_orgId();
	if ($bu_org_i->cash_ac_id) {
	 $cash_ac_id = $bu_org_i->cash_ac_id;
	} else {
	 echo "Cash ac doesnot exist.Using default account";
	 $cash_ac_id = 300;
	}

	$cash_gjl = new gl_journal_line();
	$cash_gjl->gl_journal_header_id = $this->gl_journal_header_id;
	$cash_gjl->line_num = 1;
	$cash_gjl_i = $cash_gjl->findBy_headerId_lineNum();
	if ($cash_gjl_i) {
	 $cash_gjl->gl_journal_line_id = $cash_gjl_i->gl_journal_line_id;
	}
	$cash_gjl->status = 'U';
	$cash_gjl->code_combination_id = $cash_ac_id;
	$cash_gjl->total_dr = $this->header_amount;
	$cash_gjl->total_ac_dr = $this->header_amount;
	$cash_gjl->description = 'AR Receipt of ' . $this->receipt_number;
	$cash_gjl->reference_type = 'table';
	$cash_gjl->reference_key_name = 'ar_receipt_header';
	$cash_gjl->reference_key_value = $this->ar_receipt_header_id;
	$cash_gjl->audit_trial();

	try {
	 $cash_gjl->save();
	 echo "<br> Cash Ac is Cr. Journal Line Id is " . $cash_gjl->gl_journal_line_id;
	} catch (Exception $e) {
	 echo "<br>Updating gl journal line for Cash Ac failed" . $e->getMessage();
	}


	//	Cr the receviable account 
	$arrl = new ar_receipt_line();
	$arth = new ar_transaction_header();
	$line_num = 1;
	$all_receipt_lines = $arrl->findBy_parentId($this->ar_receipt_header_id);
	foreach ($all_receipt_lines as $receipt_lines) {
	 $line_num++;
	 $ar_transaction_header_id = $receipt_lines->ar_transaction_header_id;
	 $arth_i = $arth->findBy_id($ar_transaction_header_id);
	 $receviable_gjl = new gl_journal_line();
	 $receviable_gjl->gl_journal_header_id = $this->gl_journal_header_id;
	 $receviable_gjl->line_num = $line_num;
	 $receviable_gjl_i = $receviable_gjl->findBy_headerId_lineNum();
	 if ($receviable_gjl_i) {
		$receviable_gjl->gl_journal_line_id = $receviable_gjl_i->gl_journal_line_id;
	 }
	 $receviable_gjl->status = 'U';
	 $receviable_gjl->code_combination_id = $arth_i->receivable_ac_id;
	 $receviable_gjl->total_cr = $receipt_lines->amount;
	 $receviable_gjl->total_ac_cr = $receipt_lines->amount;
	 if (!empty($this->transaction_number)) {
		$receviable_gjl->description = 'AR Trnx Receviable of ' . $this->transaction_number;
	 } else {
		$receviable_gjl->description = 'AR Trnx Receviable of ' . $this->ar_transaction_header_id;
	 }
	 $receviable_gjl->reference_type = 'table';
	 $receviable_gjl->reference_key_name = 'ar_transaction_header';
	 $receviable_gjl->reference_key_value = $this->ar_transaction_header_id;
	 $receviable_gjl->audit_trial();
	 $receviable_gjl->save();
	}
 }

 public static function instantiate_extra_fields(&$array_of_objects) {
	if (count($array_of_objects) > 0) {
	 foreach ($array_of_objects as &$this_object) {
		$supplier_details = supplier::find_by_id($this_object->ar_customer_id);
		$this_object->supplier_name = $supplier_details->supplier_name;
		$this_object->customer_number = $supplier_details->customer_number;
		$ar_customer_site_details = ar_customer_site::find_by_id($this_object->ar_customer_site_id);
		$this_object->ar_customer_site_name = $ar_customer_site_details->ar_customer_site_name;
	 }
	}
	return $array_of_objects;
 }

 Public static function receipt_types() {
	$option_header = option_header::find_by_name('AR_RECEIPT_TYPE');
	$transaction_types = option_line::find_by_option_id($option_header->option_header_id);
	return $transaction_types;
 }

 Public static function ar_approval_status() {
	$option_header = option_header::find_by_name('APPROVAL_STATUS');
	$ar_approval_status = option_line::find_by_option_id($option_header->option_header_id);
	return $ar_approval_status;
 }

 public function copy($ar_receipt_header_id) {
	global $db;
	$sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM ar_receipt_header WHERE `ar_receipt_header_id` = '{$ar_receipt_header_id}' ";
	if ($db->query($sql1)) {
	 $sql2 = "  UPDATE tmptable SET `ar_receipt_header_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `ar_receipt_header_id` = '{$ar_receipt_header_id}' ";
	 if ($db->query($sql2)) {
		$sql3 = " INSERT INTO `ar_receipt_header` SELECT * FROM tmptable WHERE `ar_receipt_header_id` = '' ";
		if ($db->query($sql3)) {
		 $this->ar_receipt_header_id = $db->insert_id();
		 $this->msg = 1;
		} else {
		 $this->msg = 0;
		}
	 }
	}
	return $this->msg;
 }

 public function save() {
	$primary_column = static::$primary_column;
	if (empty($this->$primary_column)) {
	 $this->approval_status = 'ENTER';
	 $this->create();
	} else {
	 $this->update($this->$primary_column);
	}
	return $this->msg;
 }

 /* 1. Reverse the journal header
	* 2. Update the PO lines
	* 3. Update the transaction header & line 
	*/

 private function _cancel_transaction() {
	if (empty($this->ar_receipt_header_id)) {
	 echo "<br>Cancellation failed!. No transaction header id found.";
	}
	if (!empty($this->gl_journal_header_id)) {
	 $gjh = new gl_journal_header();
	 $gjh_i = $gjh->findBy_id($this->gl_journal_header_id);
	 foreach ($gjh_i as $key => $value) {
		$gjh->$key = $value;
	 }
	 $gjh->status = 'REVERSED';
	 try {
		$gjh->_before_save();
	 } catch (Exception $e) {
		echo "Journal Reversal Failed!. Error @ class_ar_receipt_header _cancel_transaction" . $e->getMessage();
		return;
	 }
	}

	//update PO & invoice
	try {
	 $this->_cancel_transaction_poInv_lines();
	 try {
		$this->_cancel_transaction_header();
	 } catch (Exception $e) {
		echo "PO Header Update Failed!. Error @ class_ar_receipt_header _cancel_transaction" . $e->getMessage();
		return;
	 }
	} catch (Exception $e) {
	 echo "PO Detail Update Failed!. Error @ class_ar_receipt_header _cancel_transaction" . $e->getMessage();
	 return;
	}
 }

 private function _cancel_transaction_header() {
	$new_apth = new ar_receipt_header();
	$new_apth_i = $new_apth->findBy_id($this->ar_receipt_header_id);
	$new_apth->approval_status = 'CANCELLED';
	$new_apth->header_amount = '0.0';
	$new_apth->ar_receipt_header_id = $new_apth_i->ar_receipt_header_id;
	$new_apth->audit_trial();
	pa($new_apth);
	try {
	 $new_apth->save();
	} catch (Exception $e) {
	 echo "AR Transaction Lines Update Failed!. Error @ class_ar_receipt_header _transaction_cancell_poInv_lines " . $e->getMessage();
	 return;
	}
 }

 private function _cancel_transaction_poInv_lines() {
	$aptl = new ar_receipt_line();
	$all_lines = $aptl->findBy_parentId($this->ar_receipt_header_id);
	foreach ($all_lines as $lines) {

	 if (!empty($lines->po_detail_id)) {
		$po_detail = new po_detail();
		$po_detail_i = $po_detail->findBy_id($lines->po_detail_id);
		$po_detail->po_detail_id = $po_detail_i->po_detail_id;
		$po_detail->invoiced_quantity = $po_detail->invoiced_quantity - $lines->inv_line_quantity;
		$po_detail->audit_trial();
		try {
		 $po_detail->save();
		} catch (Exception $e) {
		 echo "PO Details Update Failed!. Error @ class_ar_receipt_header _transaction_cancell_poInv_lines " . $e->getMessage();
		 return;
		}
	 }
//update the invlice details
	 $aptd = new ar_receipt_detail();
	 $all_details = $aptd->findBy_parentId($lines->ar_receipt_line_id);
	 foreach ($all_details as $details) {
		$new_aptd = new ar_receipt_detail();
		$new_aptd_i = $new_aptd->findBy_id($details->ar_receipt_detail_id);
		$new_aptd->status = 'Cancelled';
		$new_aptd->amount = '0.0';
		$new_aptd->ar_receipt_detail_id = $new_aptd_i->ar_receipt_detail_id;
		$new_aptd->audit_trial();
		try {
		 $new_aptd->save();
		} catch (Exception $e) {
		 echo "AR Transaction Details Update Failed!. Error @ class_ar_receipt_header _transaction_cancell_poInv_lines " . $e->getMessage();
		 return;
		}
	 }

	 //update the invoice lines
	 $new_aptl = new ar_receipt_line();
	 $new_aptl_i = $new_aptl->findBy_id($lines->ar_receipt_line_id);
	 $new_aptl->status = 'Cancelled';
	 $new_aptl->inv_line_quantity = '0.0';
	 $new_aptl->inv_line_price = '0.0';
	 $new_aptl->ar_receipt_line_id = $new_aptl_i->ar_receipt_line_id;
	 $new_aptl->audit_trial();
	 try {
		$new_aptl->save();
	 } catch (Exception $e) {
		echo "AP Transaction Lines Update Failed!. Error @ class_ar_receipt_header _transaction_cancell_poInv_lines " . $e->getMessage();
		return;
	 }
	}
 }

 public function get_details_from_sd_so_header() {
	if (empty($this->sd_so_header_id)) {
	 return false;
	}
	$po = new sd_so_header();
	$po_i = $po->findBy_id($this->sd_so_header_id);
	$this->bu_org_id = $po_i->bu_org_id;
	$this->transaction_type = 'INVOICE';
	$this->so_number = $po_i->so_number;
	$this->ar_customer_id = $po_i->ar_customer_id;
	$this->ar_customer_site_id = $po_i->ar_customer_site_id;
	$this->document_currency = $po_i->currency;
	$this->receipt_term_id = $po_i->receipt_term_id;
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
			'show_block'
	];

	return $multi_select_hidden;
 }

}

//end of ar_receipt_header class
?>