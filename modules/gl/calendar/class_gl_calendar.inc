<?php

class gl_calendar extends dbObject {

 public static $table_name = "gl_calendar";
 public static $module = "gl";
 public static $primary_column = "gl_calendar_id";
 public static $key_column = "name";
 public $fields_inForm_notInDataBase = [
 ];
 public $fields_inHeader_needsToBeInserted_inPOST = [
		 'option_line_code'
 ];
 public $field_a = ['gl_calendar_id',
		 'option_line_code',
		 'adjustment_period_cb',
		 'name',
		 'calendar_type',
		 'year',
		 'quarter',
		 'number',
		 'from_date',
		 'to_date',
		 'name_prefix',
		 'ef_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
  public $initial_search = [
		 'name',
		 'year',
		 'quarter',
		 'name_prefix'
 ];
 public $column = [
		 'name',
		 'year',
		 'quarter',
		 'number',
		 'from_date',
		 'to_date',
		 'name_prefix'
 ];
 public $requiredField = [
		 'option_line_code',
		 'name',
		 'calendar_type',
		 'year',
		 'quarter',
		 'from_date',
		 'to_date',
		 'name_prefix'
 ];
 public $account = [
		 'combination'
 ];
 public $checkbox = [
		 'adjustment_period_cb',
 ];
 public $search = [
		 '_update_path' => 'form.php?class_name=gl_calendar',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update Calendar',
		 '_view_path' => 'modules/gl/ledger/calendar_view',
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " Ledger - Find All Calendars "; //page Title
 public $option_list = [
		 'option_line_code' => 'GL_CALENDAR_NAME',
		 'calendar_type' => 'GL_PERIOD_TYPE'
 ]; //list of search fields wh

 //gl_calendar name is stored in OP

 function __construct() {
	if (!empty(static::$table_name)) {
	 $this->field_a = get_dbColumns(static::$table_name);
	 foreach ($this->field_a as $key => $value) {
		$this->$value = '';
	 }
	}
 }

 Public static function gl_calendar_names() {
	$option_header = option_header::find_by_name('GL_CALENDAR_NAME');
	$ol = new option_line();
	$option_lines = $ol->findBy_parentId($option_header->option_header_id);
	return $option_lines;
 }

 Public static function period_types() {
	$option_header = option_header::find_by_name('GL_PERIOD_TYPE');
	$option_lines = option_line::find_by_option_id($option_header->option_header_id);
	return $option_lines;
 }

 public function find_periodNames_from_calendar($calendar_name) {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE option_line_code= :option_line_code ";
	$param_a = ['option_line_code'];
	$value_a = ['option_line_code' => $calendar_name];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return $result;
 }

 public function find_all_ofyear($year) {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE year= :year ";
	$param_a = ['year'];
	$value_a = ['year' => $year];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return $result;
 }

 public function find_highest_number_inaYear($year) {
	$numbers_in_the_year = [];
	$periods_of_year = $this->find_all_ofyear($year);
	foreach ($periods_of_year as $period) {
	 array_push($numbers_in_the_year, $period->number);
	}
	return max($numbers_in_the_year);
 }

 public function find_next_period_after_calendarId($calendar_id) {
	global $db;
	$current_cal = $this->findBy_id($calendar_id);
	$current_year = $current_cal->year;
	$current_number = $current_cal->number;
	$option_line_code = $current_cal->option_line_code;

	$highest_number_of_year = $this->find_highest_number_inaYear($current_year);
	if ($current_number < $highest_number_of_year) {
	 //next number is the next period
	 $next_period = $this->find_by_year_and_number($current_year, $current_number + 1, $option_line_code);
	} else {
	 //find first number of next year
	 $next_period = $this->find_by_year_and_number($current_year + 1, 1, $option_line_code);
	}
	return $next_period;
 }

 public function find_by_year_and_number($year, $number, $option_line_code) {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE year= :year AND number= :number AND option_line_code= :option_line_code";
	$sql .= " LIMIT 1 ";
	$param_a = ['year', 'number', 'option_line_code'];
	$value_a = ['year' => $year, 'number' => $number, 'option_line_code' => $option_line_code];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return $result;
 }

 public static function find_all_from_coa($coa_id) {
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " WHERE coa_id='{$coa_id}'";
	$result = self::find_by_sql($sql);
	return $result;
 }

 public static function find_gl_calendar_by_coa_id($coa_id) {
	$sql = "SELECT * FROM "
					. self::$table_name
					. " where coa_id={$coa_id}";
	$result = self::find_by_sql($sql);
	return $result;
 }

 public static function find_gl_calendar_by_gl_calendar($gl_calendar) {
	global $db;
	$sql = " SELECT combination FROM "
					. self::$table_name
					. " where combination LIKE '%{$gl_calendar}%' LIMIT 0, 30";
	$result = $db->find_by_sql($sql);
	$data = array();
	foreach ($result as $obj) {
	 $data[] = array(
			 'label' => $obj->combination,
			 'value' => $obj->combination
	 );
	}
	return $data;
 }

 public static function validate_gl_calendar($coa_id, $gl_calendar) {
	global $db;
	$sql = "SELECT * FROM " .
					self::$table_name .
					" where coa_id='{$coa_id}' " .
					" AND combination='{$gl_calendar}' " .
					"LIMIT 1";
	$result_set = $db->find_by_sql($sql);
	return !(empty($result_set)) ? true : false;
 }

 public static function find_combination_id_from_combination($coa_id, $gl_calendar) {
	global $db;
	$sql = "SELECT gl_calendar_id FROM " .
					self::$table_name .
					" where coa_id={$coa_id}" .
					" AND combination='{$gl_calendar}' " .
					" LIMIT 1";
	$result = $db->find_by_sql($sql);
	return !(empty($result)) ? array_shift($result) : false;
 }

}

//end of gl_calendar class
?>