<?php

class mdm_price_list_line extends dbObject {

 public static $table_name = "mdm_price_list_line";
 public static $primary_column = "mdm_price_list_line_id";
 public static $parent_primary_column = "mdm_price_list_header_id";
 public static $key_column = "line_type";
 public static $module = "mdm";
 public $field_a = [
		 'mdm_price_list_line_id',
		 'mdm_price_list_header_id',
		 'line_type',
		 'org_id',
		 'item_id',
		 'uom_id',
		 'unit_price',
		 'formula',
		 'effective_start_date',
		 'effective_end_date',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date'
 ];
 public $checkbox = [
//		 "parent_cb",
 ];
 public $initial_search = [
		 'mdm_price_list_line_id',
		 'mdm_price_list_header_id',
		 'line_type',
		 'item_id',
 ];
 public $column = [
		 'mdm_price_list_line_id',
		 'mdm_price_list_header_id',
		 'line_type',
		 'item_id',
 ];
 public $requiredField = [
		 'mdm_price_list_header_id',
		 'line_type',
 ];
 public $fields_inHeader_needsToBeInserted_inPOST = [
		 "mdm_price_list_header_id"
 ];
 public $fields_inForm_notInDataBase = [
		 "item_number",
		 'item_description',
 ];
 public $pageTitle = " Price List Line "; //page Title
 public $mdm_price_list_line_id;
 public $mdm_price_list_header_id;
 public $line_type;
 public $org_id;
 public $item_id;
 public $uom_id;
 public $unit_price;
 public $formula;
 public $effective_start_date;
 public $effective_end_date;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $item_number;
 public $item_description;

 public function __set($name, $value) {
	$this->$name = $value;
 }

 public static function find_all_lines() {
	$sql = " SELECT * FROM " . self::$table_name;
	$result = self::find_by_sql($sql);
	return $result;
 }

 public static function find_by_header_id($id) {
	$vgl = new mdm_price_list_line();
	return $vgl->findBy_parentId($id);
 }

 public static function find_by_optionId_lineCode($header_id, $code) {
	$sql = "SELECT * FROM " . self::$table_name .
					" where code={$code} AND mdm_price_list_header_id={$header_id} LIMIT 1 ";
	$result = self::find_by_sql($sql);
	return !empty($result) ? array_push($result) : $result;
 }

 public function _before_save() {
	if (!(empty($this->org_id))) {
	 if (!(empty($this->item_number))) {
		$item_s = item::find_by_itemNumber_orgId($this->item_number, $this->org_id);
		$this->item_id = $item_s->item_id;
	 }
	}
 }

}

//end of path class
?>