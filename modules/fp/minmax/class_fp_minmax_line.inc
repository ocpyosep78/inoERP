<?php

class fp_minmax_line extends dbObject {

 public static $table_name = "fp_minmax_line";
 public static $primary_column = "fp_minmax_line_id";
 public static $key_column = 'item_id';
 public static $module = "org";
 public $field_a = [
		 'fp_minmax_line_id',
		 'fp_minmax_header_id',
		 'item_id',
		 'min_quantity',
		 'max_quantity',
		 'mb_min_quantity',
		 'mb_max_quantity',
		 'mb_bin_size',
		 'total_demand',
		 'avg_daily_demand',
		 'lead_time',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 public $initial_search = [
		 'fp_minmax_line_id',
		 'fp_minmax_header_id',
		 'item_id',
 ];
 public $column = [
		 'fp_minmax_line_id',
		 'fp_minmax_header_id',
		 'item_id',
		 'min_quantity',
		 'max_quantity',
		 'mb_min_quantity',
		 'mb_max_quantity',
		 'mb_bin_size',
		 'avg_daily_demand',
 ];
 public $requiredField = [
		 'fp_minmax_header_id',
		 'item_id',
 ];
 public $fp_minmax_line_id;
 public $fp_minmax_header_id;
 public $item_id;
 public $min_quantity;
 public $max_quantity;
 public $mb_min_quantity;
 public $mb_max_quantity;
 public $mb_bin_size;
 public $total_demand;
 public $avg_daily_demand;
 public $lead_time;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

}

?>
