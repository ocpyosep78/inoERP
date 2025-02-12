<?php

class gl_period extends dbObject {

 public static $table_name = "gl_period";
 public static $dependent_classes = ['gl_calendar'];
 public static $module = "gl";
 public static $primary_column = "gl_period_id";
 public static $key_column = "gl_calendar_id";
 public $field_a = [
		 'gl_period_id',
		 'gl_calendar_id',
		 'ledger_id',
		 'period_name',
		 'status',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
 public $initial_search = [
		 'gl_period_id',
		 'period_name',
		 'ledger_id',
		 'status',
		 'name_prefix'
 ];
 public $column = [
		 'gl_period_id',
		 'period_name',
		 'ledger_id',
		 'status',
		 'name_prefix'
 ];
 public $requiredField = [
		 'gl_calendar_id',
		 'ledger_id',
		 'period_name',
		 'status',
 ];
 public $search = [
		 '_update_path' => 'form.php?class_name=gl_period&mode=9',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_view_path' => 'form.php?class_name=gl_period&mode=2',
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " GL Period - Find All Periods "; //page Title
 public $option_list = [
		 'gl_period_status' => 'GL_PERIOD_STATUS',
 ]; //list of search fields wh
 public $gl_period_id;
 public $gl_calendar_id;
 public $ledger_id;
 public $period_name;
 public $status;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $current_open_period;
 public $next_open_period;
 public $name;
 public $year;
 public $number;
 public $from_date;
 public $to_date;
 public $quarter;
 public $en_dis;

 public function _before_save() {
	if (empty($this->period_name) && (!empty($this->gl_calendar_id))) {
	 $gc = new gl_calendar();
	 $gc_i = $gc->findBy_id($this->gl_calendar_id);
	 $this->period_name = $gc_i->name;
	}
 }

 public function _after_save() {
	//perform all period opening activities
	if ($this->status == 'OPEN') {
	 $last_period = $this->previuos_period($this->gl_period_id);
	 if (!empty($last_period)) {
		$gb = new gl_balance();
		$gb->period_id = $this->gl_period_id;
		$gb->period_open_activities($last_period->gl_period_id, $this->gl_period_id);
	 }
	} else if ($this->status == 'CLOSED') {
	 $next_period = $this->next_period($this->gl_period_id);
	 if (!empty($next_period)) {
		$gb = new gl_balance();
		$gb->period_id = $next_period->gl_period_id;
		$gb->period_open_activities($this->gl_period_id, $next_period->gl_period_id);
	 }
	}
 }

 Public static function gl_period_status() {
	$option_header = option_header::find_by_name('GL_PERIOD_STATUS');
	$ol = new option_line();
	$option_lines = $ol->findBy_parentId($option_header->option_header_id);
	return $option_lines;
 }

 public function find_by_ledgerId_calendarId($ledger_id, $calendar_id) {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE ledger_id= :ledger_id  AND gl_calendar_id= :gl_calendar_id ";
	$param_a = ['ledger_id', 'gl_calendar_id'];
	$value_a = ['ledger_id' => $ledger_id, 'gl_calendar_id' => $calendar_id];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 public function find_all_periods_ofLedger($ledger_id) {
	global $db;
	$nl = new gl_ledger();
	$ledger_ob = $nl->findBy_id($ledger_id);
	$nc = new gl_calendar();
	$periods = $nc->find_periodNames_from_calendar($ledger_ob->calendar_option_line_code);
	return $periods;
 }

 public function current_open_period($ledger_id, $status = 'OPEN') {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE ledger_id= :ledger_id  AND status = :status";
	$sql .= " ORDER BY gl_period_id DESC ";
	$sql .= " LIMIT 1 ";
	$param_a = ['ledger_id', 'status'];
	$value_a = [
			'ledger_id' => $ledger_id,
			'status' => $status];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 public function find_all_periods_by_ledgerId($ledger_id, $status = '') {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE ledger_id= :ledger_id  ";
	$sql .= " ORDER BY gl_period_id DESC ";
	$param_a = ['ledger_id'];
	$value_a = [ 'ledger_id' => $ledger_id];
	if (!empty($status)) {
	 $sql .= " AND status = :status";
	 array_push($param_a, 'status');
	 $value_a['status'] = $status;
	}

	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 public function find_all_periods($ledger_id, $status = '') {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE ledger_id= :ledger_id  ";
	$param_a = ['ledger_id'];
	$value_a = [ 'ledger_id' => $ledger_id];
	if (!empty($status)) {
	 $sql .= " AND status = :status";
	 array_push($param_a, 'status');
	 $value_a['status'] = $status;
	}
	$sql .= " ORDER BY gl_period_id DESC ";
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? $result : false;
 }

 public static function current_open_period_st($ledger_id) {
	return $this->current_open_period($ledger_id);
 }

 public function next_open_period($ledger_id) {
	global $db;
	$current_open_period = $this->current_open_period($ledger_id, 'OPEN');
	$current_op_calendar_id = $current_open_period->gl_calendar_id;
	$nc = new gl_calendar();
	$next_period = $nc->find_next_period_after_calendarId($current_op_calendar_id);
	return $next_period;
 }

 public function previuos_period($current_period_id) {
	global $db;
	$current_period = $this->findBy_id($current_period_id);
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE ledger_id= :ledger_id  ";
	$sql .= " AND gl_period_id < :gl_period_id  ";
	$sql .= " ORDER BY gl_period_id DESC ";
	$sql .= " LIMIT 1 ";
	$param_a = ['ledger_id', 'gl_period_id'];
	$value_a = [ 'ledger_id' => $current_period->ledger_id,
			'gl_period_id' => $current_period->gl_period_id
	];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 public function next_period($current_period_id) {
	global $db;
	$current_period = $this->findBy_id($current_period_id);
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE ledger_id= :ledger_id  ";
	$sql .= " AND gl_period_id > :gl_period_id  ";
	$sql .= " ORDER BY gl_period_id ASC ";
	$sql .= " LIMIT 1 ";
	$param_a = ['ledger_id', 'gl_period_id'];
	$value_a = [ 'ledger_id' => $current_period->ledger_id,
			'gl_period_id' => $current_period->gl_period_id
	];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

// public static function find_gl_period_by_coa_id($coa_id) {
//	$sql = "SELECT * FROM "
//					. self::$table_name
//					. " where coa_id={$coa_id}";
//	$result = self::find_by_sql($sql);
//	return $result;
// }
//
// public static function find_gl_period_by_gl_period($gl_period) {
//	global $db;
//	$sql = " SELECT combination FROM "
//					. self::$table_name
//					. " where combination LIKE '%{$gl_period}%' LIMIT 0, 30";
//	$result = $db->find_by_sql($sql);
//	$data = array();
//	foreach ($result as $obj) {
//	 $data[] = array(
//			 'label' => $obj->combination,
//			 'value' => $obj->combination
//	 );
//	}
//	return $data;
// }
//
// public static function validate_gl_period($coa_id, $gl_period) {
//	global $db;
//	$sql = "SELECT * FROM " .
//					self::$table_name .
//					" where coa_id='{$coa_id}' " .
//					" AND combination='{$gl_period}' " .
//					"LIMIT 1";
//	$result_set = $db->find_by_sql($sql);
//	return !(empty($result_set)) ? true : false;
// }
//
// public static function find_combination_id_from_combination($coa_id, $gl_period) {
//	global $db;
//	$sql = "SELECT gl_period_id FROM " .
//					self::$table_name .
//					" where coa_id={$coa_id}" .
//					" AND combination='{$gl_period}' " .
//					" LIMIT 1";
//	$result = $db->find_by_sql($sql);
//	return !(empty($result)) ? array_shift($result) : false;
// }
}

//end of gl_period class
?>