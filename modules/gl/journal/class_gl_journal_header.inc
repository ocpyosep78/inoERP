<?php

class gl_journal_header extends dbObject {

 public static $table_name = "gl_journal_header";
 public static $dependent_classes = ['gl_journal_line'];
 public static $primary_column = "gl_journal_header_id";
 public static $multi_search_primary_column = "gl_journal_header_id";
 public static $key_column = 'ledger_id';
 public static $module = "gl";
 public $checkbox = [
		 "rev_enabled_cb"
 ];
 public $field_a = [
		 'gl_journal_header_id',
		 'ledger_id',
		 'currency',
		 'document_date',
		 'period_id',
		 'journal_source',
		 'journal_category',
		 'journal_name',
		 'description',
		 'balance_type',
		 'post_date',
		 'header_amount',
		 'exchange_type',
		 'exchange_date',
		 'exchange_rate',
		 'control_total',
		 'running_total_dr',
		 'running_total_cr',
		 'running_toatl_ac_dr',
		 'running_toatl_ac_cr',
		 'reference_type',
		 'reference_key_name',
		 'reference_key_value',
		 'ef_id',
		 'status',
		 'rev_enabled_cb',
		 'rev_number',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 public $initial_search = [
		 'gl_journal_header_id',
		 'ledger_id',
		 'currency',
		 'period_id',
		 'journal_name',
		 'description',
 ];
 public $column = [
		 'gl_journal_header_id',
		 'ledger_id',
		 'currency',
		 'period_id',
		 'journal_name',
		 'description',
 ];
 public $requiredField = [
		 'ledger_id',
		 'currency',
		 'period_id',
		 'journal_source',
		 'journal_category',
		 'journal_name',
		 'description'
 ];
 public $numberField = [
		 'header_amount',
		 'exchange_rate',
		 'control_total',
		 'running_total_dr',
		 'running_total_cr',
		 'running_toatl_ac_dr',
		 'running_toatl_ac_cr',
 ];
 public $fields_inForm_notInDataBase = [
		 'existing_status',
		 'multi_action_class'
 ];
 public $search = [
//		 '_update_path' => 'modules/po/po',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " GL Journal Entry "; //page Title
 public $option_lists = [
		 'gl_journal_category' => 'GL_JOURNAL_CATEGORY',
		 'gl_journal_status' => 'GL_JOURNAL_STATUS',
		 'gl_balance_type' => 'GL_BALANCE_TYPE',
 ];

 public $gl_journal_header_id;
 public $ledger_id;
 public $currency;
 public $period_id;
 public $document_date;
 public $journal_source;
 public $journal_category;
 public $journal_name;
 public $description;
 public $balance_type;
 public $post_date;
 public $header_amount;
 public $exchange_type;
 public $exchange_date;
 public $exchange_rate;
 public $control_total;
 public $running_total_dr;
 public $running_total_cr;
 public $running_toatl_ac_dr;
 public $running_toatl_ac_cr;
 public $reference_type;
 public $reference_key_name;
 public $reference_key_value;
 public $ef_id;
 public $status;
 public $rev_enabled_cb;
 public $rev_number;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $coa_id;
 public $coa_structure_id;
 public $existing_status;
 public $multi_action_class;
 public $multi_action_class_pc;
 public $multi_action_class_pc_value;
 private $_update_ledger_id = false;

 public function __set($name, $value) {
	switch ($value) {
	 case $value:


		break;

	 default:
		$this->$name = $value;
		break;
	}
 }

 private function _period_status($period_id) {
	$period = new gl_period();
	$period_i = $period->findBy_id($period_id);
	return $period_i->status;
 }

 public function _before_save() {

	/* Check the existing status - If its POSTED then now other actiity is allowed except Reverse */
	if ((isset($this->existing_status)) && ($this->existing_status == 'POSTED') && ( $this->status != 'REVERSED')) {
	 echo " You cant save any records as the journal is POSTED. <br>"
	 . " You can only reverse this Journal. ";
	 return -99;
	} elseif (( $this->status != 'REVERSED') && (!empty($this->gl_journal_header_id))) { //required if user click post twice
	 $gjh_id = $this->gl_journal_header_id;
	 $gjh = new gl_journal_header;
	 $gjh_inDb = $gjh->findBy_id($gjh_id);
	 if ($gjh_inDb->status == 'POSTED') {
		echo " You cant save any records as the journal is POSTED. <br>"
		. " You can only reverse this Journal. ";
		return -99;
	 }
	}

	/* If status from $_POST is empty then select the value from existing status */
	if (empty($this->status)) {
	 $this->status = $this->existing_status;
	}


	/* Reversing and Posting acttivites */
	if ($this->status === 'REVERSED') {
	 $reversing_journal_header_id = $this->gl_journal_header_id;
	 if ($this->_reverse_journal_and_lines()) {
		echo "<br> Reveser Journal creation completed. New Journal name is " . $this->journal_name . ' & id is ' . $this->gl_journal_header_id;
		echo "<br> Starting to update this journal status ";
		$gjh = new gl_journal_header();
		$gjh_i = $gjh->findBy_id($reversing_journal_header_id);
		foreach ($gjh_i as $key_i => $value_i) {
		 $gjh->$key_i = $value_i;
		}
		$gjh->status = 'REVERSED';
		$gjh->description = $gjh->description . '-Reversed on' . current_time();
		if ($gjh->save()) {
		 echo "<br> Status update complete! ";
		}
	 }
	} else if ($this->status === 'POSTED') {
	 if ($this->_period_status($this->period_id) != 'OPEN') {
		echo " <br> Period is not open";
		return -99;
	 }
	 if (empty($this->post_date)) {
		$this->post_date = current_time(1);
	 }
	} else {
	 $this->post_date = null;
	}

	/* Posting from other modules */
 }

 private function _reverse_journal_and_lines() {
	$gp = new gl_period();
	$current_open_period = $gp->current_open_period($this->ledger_id);
	$reversing_journal_header_id = $this->gl_journal_header_id;
	$this->gl_journal_header_id = null;
	$this->status = 'ENTERED';
	$this->document_date = current_time(1);
	$this->post_date = null;
	$this->period_id = $current_open_period->gl_period_id;
	$this->journal_name = 'Reversal of ' . $this->journal_name;
	$this->description = 'Reversal of ' . $this->description . ' on ' . current_time();
	$this->journal_category = 'GL_REVERSAL';
	$this->journal_source = 'System';
	$this->reference_type = 'table';
	$this->reference_key_name = 'gl_journal_header';
	$this->reference_key_value = $reversing_journal_header_id;
	$this->creation_date = current_time();
	if ((isset($_SESSION)) && (!empty($_SESSION['username']))) {
	 $this->created_by = $_SESSION['username'];
	} else {
	 $this->created_by = 'selfWeb';
	}
	$this->last_update_date = $this->creation_date;
	$this->last_update_by = $this->created_by;
	if ($this->save()) {
	 $gjl = new gl_journal_line();
	 $gjl->gl_journal_header_id = $reversing_journal_header_id;
	 try {
		$gjl->reverse_journal_lines($this->gl_journal_header_id);
	 } catch (Exception $e) {
		echo " Error in reversing " . $e->getMessage();
		return -90;
	 }
	 return 1;
	}
 }

 public function _after_save() {
//update all journals lines as posted
	if ($this->status == 'POSTED') {
	 $gjl = new gl_journal_line();
	 $gjl->gl_journal_header_id = $this->gl_journal_header_id;
	 $gjl->post_all_lines();
	}
 }

 Public function gl_balance_type() {
	$option_header = option_header::find_by_name('GL_BALANCE_TYPE');
	$ol = new option_line();
	$lines = $ol->findBy_parentId($option_header->option_header_id);
	return $lines;
 }

 Public function gl_journal_status() {
	$option_header = option_header::find_by_name('GL_JOURNAL_STATUS');
	$ol = new option_line();
	$lines = $ol->findBy_parentId($option_header->option_header_id);
	return $lines;
 }

 Public function gl_journal_category() {
	$option_header = option_header::find_by_name('GL_JOURNAL_CATEGORY');
	$ol = new option_line();
	$lines = $ol->findBy_parentId($option_header->option_header_id);
	return $lines;
 }

 public function copy($gl_journal_header_id) {
	global $db;
	$sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM gl_journal_header WHERE `gl_journal_header_id` = '{$gl_journal_header_id}' ";
	if ($db->query($sql1)) {
	 $sql2 = "  UPDATE tmptable SET `gl_journal_header_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `gl_journal_header_id` = '{$gl_journal_header_id}' ";
	 if ($db->query($sql2)) {
		$sql3 = " INSERT INTO `gl_journal_header` SELECT * FROM tmptable WHERE `gl_journal_header_id` = '' ";
		if ($db->query($sql3)) {
		 $this->gl_journal_header_id = $db->insert_id();
		 $this->msg = 1;
		} else {
		 $this->msg = 0;
		}
	 }
	}
	return $this->msg;
 }

}

//end of gl_journal_header class
?>