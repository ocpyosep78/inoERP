<?php

class fp_forecast_header extends dbObject {

 public static $table_name = "fp_forecast_header";
 public static $primary_column = "fp_forecast_header_id";
 public static $dependent_classes = ['fp_forecast_line'];
 public static $key_column = 'forecast';
 public static $module = "fp";
 public $field_a = [
		 'fp_forecast_header_id',
		 'org_id',
		 'forecast',
		 'description',
		 'status',
		 'demand_class',
		 'ar_customer_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 //variables used for showing data

 public $initial_search = [
		 'fp_forecast_header_id',
		 'org_id',
		 'forecast',
		 'description',
 ];
 public $column = [
		 'fp_forecast_header_id',
		 'org_id',
		 'forecast',
		 'description',
		 'status',
		 'demand_class',
		 'ar_customer_id',
 ];
 public $requiredField = [
		 'org_id',
		 'forecast',
		 'status',
 ];
 public $fields_inForm_notInDataBase = [
		 "customer_name",
		 "customer_number",
 ];
 public $pageTitle = " Forecast - FP  "; //page Title
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
 ];
 public $fp_forecast_header_id;
 public $org_id;
 public $forecast;
 public $description;
 public $status;
 public $demand_class;
 public $ar_customer_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

 public function _before_submit() {
	
 }

 Public static function fp_bucket() {
	$option_header = option_header::find_by_name('FP_BUCKET');
	$ol = option_line::find_by_option_id($option_header->option_header_id);
	return $ol;
 }

 Public static function demand_type() {
	$option_header = option_header::find_by_name('FP_DEMAND_TYPE');
	$type = option_line::find_by_option_id($option_header->option_header_id);
	return $type;
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
 
 public function findAll_2columns() {
	$result = $this->findAll();
	$id = self::$primary_column;
	$name = self::$key_column;
	$data = array();
	if (!empty($result)) {
	 foreach ($result as $obj) {
		$data[] = array(
				'label' => $obj->$name,
				'name' => $obj->$name,
				'id' => $obj->$id
		);
	 }
	}
	return $data;
 }

}

//end of forecast class
?>