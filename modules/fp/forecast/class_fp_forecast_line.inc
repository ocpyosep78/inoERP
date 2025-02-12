<?php

class fp_forecast_line extends dbObject {

 public static $table_name = "fp_forecast_line";
 public static $primary_column = "fp_forecast_line_id";
 public static $parent_primary_column = "fp_forecast_header_id";
 public static $key_column = 'item_id';
 public static $module = "po";
 public $field_a = [
		 'fp_forecast_line_id',
		 'fp_forecast_header_id',
		 'item_id',
		 'bucket_type',
		 'start_date',
		 'end_date',
		 'no_of_bucket',
		 'current',
		 'original',
		 'created_by',
		 'creation_date',
		 'total_current',
		 'total_original',
		 'fp_consumption_id',
		 'last_update_by',
		 'last_update_date',
 ];
 //variables used for showing data

 public $fields_inHeader_needsToBeInserted_inPOST = [
		 "fp_forecast_header_id"
 ];
 public $requiredField = [
		 'fp_forecast_header_id',
		 'item_id',
		 'bucket_type',
		 'start_date',
		 'no_of_bucket',
		 'current',
		 'original',
 ];
 public $fp_forecast_line_id;
 public $fp_forecast_header_id;
 public $item_id;
 public $bucket_type;
 public $start_date;
 public $end_date;
 public $no_of_bucket;
 public $current;
 public $original;
 public $total_current;
 public $total_original;
 public $fp_consumption_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

 public function findBy_ItemId_headerId() {
	$sql = " SELECT * FROM  ";
	$sql .= self::$table_name;
	$sql .= " WHERE fp_forecast_header_id =:fp_forecast_header_id AND item_id = :item_id ";

	$param_a = ['fp_forecast_header_id', 'item_id'];
	$value_a = ['fp_forecast_header_id' => $this->fp_forecast_header_id, 'item_id' => $this->item_id];
	$result = $this->findBy_sql($sql, $param_a, $value_a);
	return !empty($result) ? $result : false;
 }

 public function findAll_distinctItems_ofHeader() {
	$sql = "SELECT DISTINCT(item_id) FROM " .
					self::$table_name;
	$sql .= " WHERE fp_forecast_header_id =:fp_forecast_header_id ";
	$param_a = ['fp_forecast_header_id'];
	$value_a = ['fp_forecast_header_id' => $this->fp_forecast_header_id];
	$result_array = $this->findBy_sql($sql, $param_a, $value_a);
	return !empty($result_array) ? $result_array : false;
 }

}

//end of inv_transaction class
?>