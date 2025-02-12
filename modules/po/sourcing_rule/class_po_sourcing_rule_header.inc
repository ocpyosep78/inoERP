<?php

class po_sourcing_rule_header extends dbObject {

 public static $table_name = "po_sourcing_rule_header";
 public static $primary_column = "po_sourcing_rule_header_id";
 public static $dependent_classes = ['po_sourcing_rule_line'];
 public static $key_column = 'sourcing_rule';
 public static $module = "po";
 public static $system_info = [
		 'name' => 'Sourcing Rule',
		 'number' => '2202',
		 'description' => 'Create & Mainten Sourcing Rule',
		 'version' => '1.1.1.3',
		 'db_version' => '1001',
		 'mod_version' => '1.1.x-1.1',
		 'dependent_class' => array('po_sourcing_rule_line'),
		 'primary_entity_cb' => '',
		 'module_name' => 'po',
		 'weight' => 2
 ];
 public $field_a = [
		 'po_sourcing_rule_header_id',
		 'sourcing_rule',
		 'description',
		 'status',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 //variables used for showing data

 public $initial_search = [
		 'po_sourcing_rule_header_id',
		 'sourcing_rule',
		 'description',
		 'status',
 ];
 public $column = [
		 'po_sourcing_rule_header_id',
		 'sourcing_rule',
		 'description',
		 'status',
 ];
 public $requiredField = [
		 'sourcing_rule',
		 'description',
 ];
 public $pageTitle = " Sourcing Rule  "; //page Title
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
 ];
 public $po_sourcing_rule_header_id;
 public $sourcing_rule;
 public $description;
 public $status;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

 public function _before_submit() {
	
 }

 public static function find_by_sourcingRule($sourcing_rule) {
	global $db;
	$sql = "SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " where sourcing_rule = '{$sourcing_rule}' ";
	$sql .= " LIMIT 1 ";
	$result = $db->find_by_sql($sql);
	return !(empty($result)) ? array_pop($result) : false;
 }

 public function findBy_itemId() {
	$sql = "SELECT * FROM " .
					self::$table_name .
					" where item_id= :item_id LIMIT 1 ";
	$param_a = ['item_id'];
	$value_a = ['item_id' => $this->item_id];
	$result_array = $this->findBy_sql($sql, $param_a, $value_a);
	return !empty($result_array) ? array_pop($result_array) : false;
 }

}

//end of sourcing_rule class
?>