<?php

class ap_transaction_header extends dbObject {

 public static $table_name = "ap_transaction_header";
 public static $dependent_classes = ['ap_transaction_line', 'ap_transaction_detail'];
 public static $primary_column = "ap_transaction_header_id";
 public static $primary_column2 = "transaction_number";
 public static $key_column = 'supplier_id';
 public static $module = "ap"; //same as gl_journal_source
 public static $gl_journal_category = "AP_TRANSACTIONS";
 public static $system_info = [
		 'name' => ' AP Transaction ',
		 'number' => '1202',
		 'description' => 'Create & Mainten Supplier Invoice, Debit Memo, Credit Memo, PrePayments, etc',
		 'version' => '1.1.1.3',
		 'db_version' => '1001',
		 'mod_version' => '1.1.x-1.1',
		 'dependent_class' => array('ap_transaction_line', 'ap_transaction_detail', 'ap_transaction_v'),
		 'primary_entity_cb' => '',
		 'module_name' => 'ap',
		 'weight' => 2
 ];
 public $checkbox = [
//		 "rev_enabled_cb"
 ];
 public $field_a = [
		 'ap_transaction_header_id',
		 'bu_org_id',
		 'transaction_type',
		 'transaction_number',
		 'supplier_id',
		 'supplier_site_id',
		 'document_owner',
		 'description',
		 'ship_to_id',
		 'bill_to_id',
		 'header_amount',
		 'paid_amount',
		 'currency',
		 'document_currency',
		 'payment_term_id',
		 'exchange_rate_type',
		 'exchange_rate',
		 'ef_id',
		 'transaction_status',
		 'document_date',
		 'document_number',
		 'ledger_id',
		 'period_id',
		 'payment_term_date',
		 'pay_group',
		 'payment_method',
		 'approval_status',
		 'payment_status',
		 'reference_type',
		 'reference_key_name',
		 'reference_key_value',
		 'po_header_id',
		 'gl_journal_header_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
 public $initial_search = [
		 'ap_transaction_header_id',
		 'bu_org_id',
		 'ledger_id',
		 'period_id',
		 'transaction_type',
		 'transaction_number',
		 'document_number',
		 'supplier_id',
		 'supplier_site_id',
		 'document_owner',
		 'approval_status',
		 'gl_journal_header_id'
 ];
 public $column = [
		 'ap_transaction_header_id',
		 'document_number',
		 'transaction_type',
		 'transaction_number',
		 'header_amount',
		 'paid_amount',
		 'supplier_id',
		 'supplier_site_id',
		 'bu_org_id',
		 'ledger_id',
		 'period_id',
		 'document_owner',
		 'document_currency',
		 'currency',
		 'gl_journal_header_id'
 ];
 public $requiredField = [
		 'bu_org_id',
		 'transaction_type',
		 'supplier_id',
		 'supplier_site_id',
		 'header_amount',
		 'currency',
		 'payment_term_id',
		 'document_date',
		 'ledger_id',
		 'period_id'
 ];
 public $fields_inForm_notInDataBase = [
		 "supplier_name",
		 "supplier_number",
		 "supplier_site_name",
		 'po_number',
		 'po_header_id',
		 'action',
		 'transaction_action'
 ];
 public $numberField = [
		 'header_amount'
 ];
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
//		 '_view_action_meassge' => 'View',
//		 '_extra_path' => '',
		 '_extra_path' => array('form.php?class_name=ap_payment_header&mode=9' => 'Pay',
				 'form.php?class_name=ap_transaction_header&mode=9&transaction_type=DEBIT_MEMO' => 'Credit')
 ];
 public $pageTitle = " AP Transaction - Invoice, Debit/Credit Memo etc "; //page Title
 public $option_lists = [
//		 'po_type' => 'PO_TYPE',
//		 'po_status' => 'PO_STATUS',
 ];
 public $ap_transaction_header_id;
 public $bu_org_id;
 public $transaction_type;
 public $transaction_number;
 public $supplier_id;
 public $supplier_site_id;
 public $document_owner;
 public $description;
 public $ship_to_id;
 public $bill_to_id;
 public $header_amount;
 public $paid_amount;
 public $currency;
 public $document_currency;
 public $payment_term_id;
 public $exchange_rate_type;
 public $exchange_rate;
 public $ef_id;
 public $transaction_status;
 public $document_date;
 public $document_number;
 public $ledger_id;
 public $period_id;
 public $payment_term_date;
 public $pay_group;
 public $payment_method;
 public $approval_status;
 public $payment_status;
 public $reference_type;
 public $reference_key_name;
 public $reference_key_value;
 public $po_header_id;
 public $gl_journal_header_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $supplier_name;
 public $supplier_number;
 public $po_number;
 public $multi_action_class_pc;
 public $multi_action_class_pc_value;
 public $action;
 public $transaction_action;

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
	$apth = new ap_transaction_header();
	$apth->ap_transaction_header_id = $this->ap_transaction_header_id;
	$apth->gl_journal_header_id = $this->gl_journal_header_id;
	$apth->created_by = $this->created_by;
	$apth->creation_date = $this->creation_date;
	$apth->last_update_by = $this->last_update_by;
	$apth->last_update_date = $this->last_update_date;
	$apth->save();
 }

 public function _before_save() {

	if ((!empty($this->ap_transaction_header_id)) && ($this->action === 'create_accounting')) {
	 $asis_data = $this->findBy_id($this->ap_transaction_header_id);
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

	if ((!empty($this->ap_transaction_header_id)) && ($this->transaction_action == 'CANCEL')) {
	 $this->_cancel_transaction();
	 return 10;
	}
 }

 public function _after_save() {
	global $db;
	if (!$this->transaction_number) {
	 echo '<br/> No transaction number is entered';
	}
	if ((!empty($this->ap_transaction_header_id)) && empty($this->transaction_number)) {
	 $ap_transaction_header_id = $this->ap_transaction_header_id;
	 $bu_org_id = $this->bu_org_id;
	 $this->transaction_number = $bu_org_id . '-' . $ap_transaction_header_id;
	 echo '<br/> System created transaction number is ' . $this->transaction_number;
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
	$gjh->reference_key_value = $this->ap_transaction_header_id;
	$gjh->journal_name = $gjh->journal_category . '-' . $gjh->reference_key_value;
	$gjh->description = $gjh->journal_name . '-' . current_time();
	$gjh->balance_type = 'A';
	$gjh->audit_trial();
	$gjh->save();
	$this->gl_journal_header_id = $gjh->gl_journal_header_id;
 }

 private function _save_journal_lines() {
	$aptl = new ap_transaction_line();
	$all_lines = $aptl->findBy_parentId($this->ap_transaction_header_id);
	foreach ($all_lines as $lines) {
	 $aptd = new ap_transaction_detail();
	 $all_details = $aptd->findBy_parentId($lines->ap_transaction_line_id);
	 foreach ($all_details as $deatils) {
		$new_gjl = new gl_journal_line();
		$new_gjl->gl_journal_header_id = $this->gl_journal_header_id;
		$new_gjl->line_num = $deatils->detail_number;
		$new_gjl_i = $new_gjl->findBy_headerId_lineNum();
		$new_gjl->gl_journal_line_id = $new_gjl_i->gl_journal_line_id;
		$new_gjl->status = 'U';
		$new_gjl->code_combination_id = $deatils->detail_ac_id;
		$new_gjl->total_dr = $deatils->amount;
		$new_gjl->total_ac_dr = $deatils->amount;
		$new_gjl->description = 'AP Trnx detail #' . $deatils->detail_number . ' of trxn# ' . $this->transaction_number;
		$new_gjl->reference_type = 'table';
		$new_gjl->reference_key_name = 'ap_transaction_detail';
		$new_gjl->reference_key_value = $deatils->ap_transaction_detail_id;
		$new_gjl->audit_trial();
		$new_gjl->save();
	 }
	}

//	save the liability account
	$sbu = new supplier_bu();
	$sbu_i = $sbu->findBy_orgId_supplierId($this->bu_org_id, $this->supplier_id);
	if ($sbu_i->liability_account_id) {
	 $liability_account_id = $sbu_i->liability_account_id;
	} else {
	 echo "Supplier liability ac doesnot exist.Using BU level default account";
	 $liability_account_id = 300;
	}

	$liability_gjl = new gl_journal_line();
	$liability_gjl->gl_journal_header_id = $this->gl_journal_header_id;
	$liability_gjl->line_num = 999;
	$liability_gjl_i = $liability_gjl->findBy_headerId_lineNum();
	$liability_gjl->gl_journal_line_id = $liability_gjl_i->gl_journal_line_id;
	$liability_gjl->status = 'U';
	$liability_gjl->code_combination_id = $liability_account_id;
	$liability_gjl->total_cr = $this->header_amount;
	$liability_gjl->total_ac_cr = $this->header_amount;
	$liability_gjl->description = 'AP Trnx Liability of ' . $this->transaction_number;
	$liability_gjl->reference_type = 'table';
	$liability_gjl->reference_key_name = 'ap_transaction_header';
	$liability_gjl->reference_key_value = $this->ap_transaction_header_id;
	$liability_gjl->audit_trial();
	$liability_gjl->save();
 }

 public static function instantiate_extra_fields(&$array_of_objects) {
	if (count($array_of_objects) > 0) {
	 foreach ($array_of_objects as &$this_object) {
		$supplier_details = supplier::find_by_id($this_object->supplier_id);
		$this_object->supplier_name = $supplier_details->supplier_name;
		$this_object->supplier_number = $supplier_details->supplier_number;
		$supplier_site_details = supplier_site::find_by_id($this_object->supplier_site_id);
		$this_object->supplier_site_name = $supplier_site_details->supplier_site_name;
	 }
	}
	return $array_of_objects;
 }

 Public static function transaction_types() {
	$option_header = option_header::find_by_name('AP_TRANSACTION_TYPE');
	$transaction_types = option_line::find_by_option_id($option_header->option_header_id);
	return $transaction_types;
 }

 Public static function ap_approval_status() {
	$option_header = option_header::find_by_name('APPROVAL_STATUS');
	$ap_approval_status = option_line::find_by_option_id($option_header->option_header_id);
	return $ap_approval_status;
 }

 public function copy($ap_transaction_header_id) {
	global $db;
	$sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM ap_transaction_header WHERE `ap_transaction_header_id` = '{$ap_transaction_header_id}' ";
	if ($db->query($sql1)) {
	 $sql2 = "  UPDATE tmptable SET `ap_transaction_header_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `ap_transaction_header_id` = '{$ap_transaction_header_id}' ";
	 if ($db->query($sql2)) {
		$sql3 = " INSERT INTO `ap_transaction_header` SELECT * FROM tmptable WHERE `ap_transaction_header_id` = '' ";
		if ($db->query($sql3)) {
		 $this->ap_transaction_header_id = $db->insert_id();
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
	 $this->ap_approval_status = 'ENTER';
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
	if (empty($this->ap_transaction_header_id)) {
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
		echo "Journal Reversal Failed!. Error @ class_ap_transaction_header _cancel_transaction" . $e->getMessage();
		return;
	 }
	}

	//update PO & invoice
	try {
	 $this->_cancel_transaction_poInv_lines();
	 try {
		$this->_cancel_transaction_header();
	 } catch (Exception $e) {
		echo "PO Header Update Failed!. Error @ class_ap_transaction_header _cancel_transaction" . $e->getMessage();
		return;
	 }
	} catch (Exception $e) {
	 echo "PO Detail Update Failed!. Error @ class_ap_transaction_header _cancel_transaction" . $e->getMessage();
	 return;
	}
 }

 private function _cancel_transaction_header() {
	$new_apth = new ap_transaction_header();
	$new_apth_i = $new_apth->findBy_id($this->ap_transaction_header_id);
	$new_apth->approval_status = 'CANCELLED';
	$new_apth->header_amount = '0.0';
	$new_apth->ap_transaction_header_id = $new_apth_i->ap_transaction_header_id;
	$new_apth->audit_trial();
	pa($new_apth);
	try {
	 $new_apth->save();
	} catch (Exception $e) {
	 echo "AP Transaction Lines Update Failed!. Error @ class_ap_transaction_header _transaction_cancell_poInv_lines " . $e->getMessage();
	 return;
	}
 }

 private function _cancel_transaction_poInv_lines() {
	$aptl = new ap_transaction_line();
	$all_lines = $aptl->findBy_parentId($this->ap_transaction_header_id);
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
		 echo "PO Details Update Failed!. Error @ class_ap_transaction_header _transaction_cancell_poInv_lines " . $e->getMessage();
		 return;
		}
	 }
//update the invlice details
	 $aptd = new ap_transaction_detail();
	 $all_details = $aptd->findBy_parentId($lines->ap_transaction_line_id);
	 foreach ($all_details as $details) {
		$new_aptd = new ap_transaction_detail();
		$new_aptd_i = $new_aptd->findBy_id($details->ap_transaction_detail_id);
		$new_aptd->status = 'Cancelled';
		$new_aptd->amount = '0.0';
		$new_aptd->ap_transaction_detail_id = $new_aptd_i->ap_transaction_detail_id;
		$new_aptd->audit_trial();
		try {
		 $new_aptd->save();
		} catch (Exception $e) {
		 echo "AP Transaction Details Update Failed!. Error @ class_ap_transaction_header _transaction_cancell_poInv_lines " . $e->getMessage();
		 return;
		}
	 }

	 //update the invoice lines
	 $new_aptl = new ap_transaction_line();
	 $new_aptl_i = $new_aptl->findBy_id($lines->ap_transaction_line_id);
	 $new_aptl->status = 'Cancelled';
	 $new_aptl->inv_line_quantity = '0.0';
	 $new_aptl->inv_line_price = '0.0';
	 $new_aptl->ap_transaction_line_id = $new_aptl_i->ap_transaction_line_id;
	 $new_aptl->audit_trial();
	 try {
		$new_aptl->save();
	 } catch (Exception $e) {
		echo "AP Transaction Lines Update Failed!. Error @ class_ap_transaction_header _transaction_cancell_poInv_lines " . $e->getMessage();
		return;
	 }
	}
 }

 public function get_details_from_po_header() {
	if (empty($this->po_header_id)) {
	 return false;
	}
	$po = new po_header();
	$po_i = $po->findBy_id($this->po_header_id);
	$this->bu_org_id = $po_i->bu_org_id;
	$this->transaction_type = 'INVOICE';
	$this->po_number = $po_i->po_number;
	$this->supplier_id = $po_i->supplier_id;
	$this->supplier_site_id = $po_i->supplier_site_id;
	$this->document_currency = $po_i->currency;
	$this->payment_term_id = $po_i->payment_term_id;
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
			'action'
	];

	return $multi_select_hidden;
 }

}

//end of ap_transaction_header class
?>