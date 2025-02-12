<?php

class onhand_v extends dbObject {

 public static $table_name = "onhand_v";
 public static $primary_column = "onhand_id";
 public $field_a = [
		 'onhand_id',
		 'item_number',
		 'item_description',
		 'org_name',
		 'subinventory',
		 'locator',
		 'uom_id',
		 'onhand',
		 'item_id',
		 'org_id',
		 'subinventory_id',
		 'locator_id',
		 'lot_id',
		 'serial_id',
		 'reservable_onhand',
		 'transactable_onhand',
		 'lot_status',
		 'serial_status',
		 'secondary_uom_id',
		 'onhand_status',
		 'ef_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 public $initial_search = [
		 'onhand_id',
		 'item_number',
		 'item_description',
		 'org_name',
		 'subinventory',
		 'locator',
		 'uom_id',
		 'onhand',
		 'item_id',
		 'org_id',
		 'subinventory_id',
		 'locator_id',
 ];
 public $column = [
		 'onhand_id',
		 'item_number',
		 'item_description',
		 'org_name',
		 'subinventory',
		 'locator',
		 'uom_id',
		 'onhand',
		 'item_id',
		 'org_id',
		 'subinventory_id',
		 'locator_id',
 ];
 public $dateField = [
 ];
 public $pageTitle = " Onhand - Find Inventory Onhand "; //page Title
 public $search_groupBy = [
		 'locator' => 'Locator',
		 'subinventory' => 'Sub Inventory',
		 'org_id' => 'Inventory Org',
 ];
 public $ra_onhand_by_subinventoryType_parameters = [
		 'Result Limit' => 'ra_result_limit',
		 'Chart Type' => 'ra_chart_type',
 ];
 public $ra_onhand_by_subinventoryType_settings = [
		 '_chart_name' => 'Onhand Quantity By Subinventory Type',
		 '_x_axis_text' => 'Onhand Quantity',
 ];
 public $ra_onhand_value_by_subinventoryType_settings = [
		 '_chart_name' => 'Onhand Value By Subinventory Type',
		 '_x_axis_text' => 'Onhand Value',
 ];
 public $ra_onhand_by_productLine_settings = [
		 '_chart_name' => 'Onhand Quantity By Product Line',
		 '_x_axis_text' => 'Onhand Quantity',
 ];
 public $ra_onhand_value_by_productLine_settings = [
		 '_chart_name' => 'Onhand Value By Product Line',
		 '_x_axis_text' => 'Onhand Value',
 ];
 public $ra_onhand_by_productLine_subinventoryType_settings = [
		 '_chart_name' => 'Onhand By Product Line Subinventory Type',
		 '_chart_width' => '750',
		 '_chart_height' => '450',
		 '_x_axis_text' => 'Onhand Quantity',
		 '_chart_type' => 'clustered_column',
		 '_gap_between_xaxis_text' =>'50',
		 '_legend' => ''
 ];
 public $ra_report_set_onhand_by_subinventoryType_settings = [
		 '_chart_name' => 'Onhand By Subinventory Type',
		 '_chart_width' => '350',
		 '_chart_height' => '350',
		 '_x_axis_text' => 'Sub Invnetory Type',
		 '_chart_type' => array('horizonatl_bar', 'vertical_column', 'pie'),
		 '_legend' => ''
 ];
 public $ra_report_set_onhand_by_subinventoryType = [
		 'ra_onhand_by_subinventoryType',
		 'ra_onhand_value_by_subinventoryType',
		 'ra_onhand_by_productLine',
		 'ra_onhand_value_by_productLine',
		 'ra_onhand_by_productLine_subinventoryType'
 ];
 public $onhand_id;
 public $item_number;
 public $item_description;
 public $product_line;
 public $org_name;
 public $subinventory;
 public $subinventory_type;
 public $locator;
 public $uom_id;
 public $onhand;
 public $item_id;
 public $org_id;
 public $subinventory_id;
 public $locator_id;
 public $lot_id;
 public $serial_id;
 public $reservable_onhand;
 public $transactable_onhand;
 public $lot_status;
 public $serial_status;
 public $secondary_uom_id;
 public $onhand_status;
 public $ef_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;


 public function __set($name, $value) {
	$this->$name = $value;
 }

 private function create_onhand_v() {
	$sql = "
	 CREATE OR REPLACE VIEW onhand_v
(onhand_id, item_number, item_description, product_line, org_name, subinventory, locator,
uom_id,onhand, standard_cost, onhand_value,
item_id, org_id, subinventory_id, subinventory_type,
locator_id, lot_id, serial_id, reservable_onhand, 
transactable_onhand, lot_status, serial_status,  
secondary_uom_id, onhand_status, ef_id, created_by, 
creation_date, last_update_by, last_update_date)
AS
SELECT onhand.onhand_id, 
item.item_number, item.item_description, item.product_line,
org.org, subinventory.subinventory, locator.locator,
onhand.uom_id,onhand.onhand,
cic.standard_cost, (onhand.onhand * cic.standard_cost) as onhand_value,
onhand.item_id, onhand.org_id, onhand.subinventory_id, subinventory.type,
onhand.locator_id, onhand.lot_id, onhand.serial_id, onhand.reservable_onhand, 
onhand.transactable_onhand, onhand.lot_status, onhand.serial_status,  
onhand.secondary_uom_id, onhand.onhand_status, onhand.ef_id, onhand.created_by, 
onhand.creation_date, onhand.last_update_by, onhand.last_update_date

FROM onhand 
LEFT JOIN item ON onhand.item_id = item.item_id
LEFT JOIN org ON onhand.org_id = org.org_id
LEFT JOIN subinventory ON onhand.subinventory_id = subinventory.subinventory_id
LEFT JOIN locator ON onhand.locator_id = locator.locator_id
LEFT JOIN cst_item_cost_v cic ON cic.item_id = onhand.item_id WHERE cic.bom_cost_type='FROZEN'
";
 }

 public function ra_report_set_onhand_by_subinventoryType() {
	$result_a = [];
	$result_a['ra_onhand_by_subinventoryType'] = $this->ra_onhand_by_subinventoryType();
	$result_a['ra_onhand_value_by_subinventoryType'] = $this->ra_onhand_value_by_subinventoryType();
	$result_a['ra_onhand_by_productLine'] = $this->ra_onhand_by_productLine();
	$result_a['ra_onhand_value_by_productLine'] = $this->ra_onhand_value_by_productLine();
	$result_a['ra_onhand_by_productLine_subinventoryType'] = $this->ra_onhand_by_productLine_subinventoryType();
	return $result_a;
 }

 public function ra_onhand_by_subinventoryType($limit_no = "5") {
	$sql = " SELECT subinventory_type, SUM(onhand) as 'Onhand'
				FROM ";
	$sql .= self::$table_name;
	$sql .= " GROUP BY subinventory_type ";
	$sql .= " ORDER BY onhand desc ";
	$sql .= " LIMIT 5 ";
	$result = $this->findBySql($sql);
//	$ret_result = ra_conevrt_data_woarray($result, 'subinventory_type', $legend);
//	$settings = &$this->ra_onhand_by_subinventoryType_settings;
//	$settings['legend'] = $legend;
	return !empty($result) ? $result : false;
 }

 public function ra_onhand_value_by_subinventoryType() {
	$sql1 = " SELECT subinventory_type, SUM(onhand_value) as 'onhand_value'
				FROM ";
	$sql1 .= self::$table_name;
	$sql1 .= " GROUP BY subinventory_type ";
	$sql1 .= " ORDER BY onhand_value desc ";
	$sql1 .= " LIMIT 5 ";
	$result1 = $this->findBySql($sql1);
	return !empty($result1) ? $result1 : false;
 }

 public function ra_onhand_by_productLine($limit_no = "5") {
	$sql = " SELECT product_line, SUM(onhand) as 'Onhand' FROM ";
	$sql .= self::$table_name;
	$sql .= " GROUP BY product_line ";
	$sql .= " ORDER BY onhand_value desc ";
	$sql .= " LIMIT $limit_no ";
	$result = $this->findBySql($sql);
	return !empty($result) ? $result : false;
 }

 public function ra_onhand_value_by_productLine($limit_no = "5") {
	$sql = " SELECT product_line, SUM(onhand_value) as 'Onhand Value' FROM ";
	$sql .= self::$table_name;
	$sql .= " GROUP BY product_line ";
	$sql .= " ORDER BY onhand_value desc ";
	$sql .= " LIMIT $limit_no ";
	$result = $this->findBySql($sql);
	return !empty($result) ? $result : false;
 }

 public function ra_onhand_by_productLine_subinventoryType() {
	$legend = [];
	$sql = " SELECT  subinventory_type, product_line , SUM(onhand)
	  FROM onhand_v
		GROUP BY subinventory_type, product_line
		ORDER BY subinventory_type, product_line ";
	$result = $this->findBySql($sql);
	$result_f = ra_conevrt_data_bar_column($result, $legend);
	$this->ra_onhand_by_productLine_subinventoryType_settings['_legend'] = $legend;
	return !empty($result_f) ? $result_f : false;
 }

}

//end of po_detail class
?>