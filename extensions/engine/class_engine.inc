<?php

class engine extends dbObject {

 public static $table_name = "engine";
 public static $module = "sys";
 public static $primary_column = "engine_id";
 public static $key_column = "obj_class_name";
 public $field_a = [
		 'engine_id',
		 'obj_class_name',
		 'number',
		 'type',
		 'enabled_cb',
		 'db_version',
		 'primary_entity_cb',
		 'module_name',
		 'path',
		 'dependent_class',
		 'weight',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 public $initial_search = [
		 'engine_id',
		 'obj_class_name',
		 'type',
		 'status',
 ];
 public $column = [
		 'engine_id',
		 'obj_class_name',
		 'type',
		 'status',
		 'db_version',
		 'primary_entity_cb',
		 'module_name',
 ];
 public $requiredField = [
		 'type',
		 'obj_class_name',
		 'module_name'
 ];
 public $checkbox = [
		 'primary_entity_cb',
		 'uninstall_cb'
 ];
 public $fields_inForm_notInDataBase = [
		 "uninstall_cb",
 ];
 public $search = [
		 '_update_path' => 'form.php?class_name=engine&mode=9',
		 '_show_update_path' => 1,
		 '_view_path' => 'form.php?class_name=engine&mode=2',
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " Engine "; //page Title
 public $engine_id;
 public $obj_class_name;
 public $type;
 public $number;
 public $enabled_cb;
 public $db_version;
 public $primary_entity_cb;
 public $module_name;
 public $path;
 public $dependent_class;
 public $weight;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $uninstall_cb;

 public function _before_save() {
//	pa($this);
//	return 10;
 }

 public function _after_save() {
	if ((!empty($this->obj_class_name)) && ($this->enabled_cb == 1)) {
	 $this_class = new $this->obj_class_name;
	 if (method_exists($this_class, '_enable')) {
		call_user_func(array($this_class, '_enable'));
	 }
	}

	if ((!empty($this->obj_class_name)) && ( empty($this->enabled_cb) || ($this->enabled_cb != 1))) {
	 $this_class = new $this->obj_class_name;
	 if (method_exists($this_class, '_disable')) {
		call_user_func(array($this_class, '_disable'));
	 }
	}
 }

 public function findBy_className($obj_class_name) {
	$sql = " SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " WHERE obj_class_name = :obj_class_name ";
	$sql .= " LIMIT 1 ";

	$value_a = ['obj_class_name' => $obj_class_name];
	$result = $this->findBySql($sql, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

}

//end of engine class
?>