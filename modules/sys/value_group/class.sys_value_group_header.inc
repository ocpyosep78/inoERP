<?php

class sys_value_group_header extends dbObject {

 public static $table_name = "sys_value_group_header";
 public static $primary_column = "sys_value_group_header_id";
 public static $dependent_classes = ['sys_value_group_line'];
 public static $key_column = "value_group";
 public static $module = "sys";
 public static $access_level_array = [
		 'system' => 'System',
		 'user' => 'User',
		 'both' => 'Both'
 ];
 public $field_a = [
		 'sys_value_group_header_id',
		 'access_level',
		 'value_group',
		 'description',
		 'module_id',
		 'validation_type',
		 'field_type',
		 'min_size',
		 'max_size',
		 'min_value',
		 'max_value',
		 'fixed_size',
		 'number_only_cb',
		 'uppercase_only_cb',
		 'option_assignments',
		 'status',
		 'rev_enabled',
		 'rev_number',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
 public $initial_search = [
		 'sys_value_group_header_id',
		 'access_level',
		 'value_group',
		 'description',
		 'validation_type',
		 'module_id'
 ];
 public $column = [
		 'sys_value_group_header_id',
		 'access_level',
		 'value_group',
		 'description',
		 'module_id',
 ];
 public $requiredField = [
		 'access_level',
		 'value_group',
		 'description',
		 'module_id'
 ];
 public $search = [
		 '_update_path' => 'modules/sys/value_group/value_group',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
//		 '_view_action_meassge' => 'View',
//		 '_extra_path' => '',
 ];
 public $pageTitle = " Value Group - Find All Calue Groups "; //page Title
 public $option_list = [
//		 'calendar_option_line_code' => 'GL_CALENDAR_NAME',
 ]; //list of search fields which have options
 public $sys_value_group_header_id;
 public $access_level;
 public $value_group;
 public $description;
 public $module_id;
 public $validation_type;
 public $option_assignments;
 public $status;
 public $rev_enabled;
 public $rev_number;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $msg;

// function __construct() {
//	global $dbc;
//	$sql_fields = " SHOW COLUMNS FROM  " . self::$table_name;
//	$prepare = $dbc->connection->prepare($sql_fields);
//	$prepare->execute();
//	$this->field_a = $prepare->fetchAll(PDO::FETCH_COLUMN, 0);
// }

 public function __set($name, $value) {
	$this->$name = $value;
 }

 Public static function validation_types() {
	$header = option_header::find_by_keyColumn('SYS_VALIDATION_TYPE');
	$option_line = new option_line();
	$lines = $option_line->findBy_parentId($header->option_header_id);
	return $lines;
 }

}

//end of path class
?>
