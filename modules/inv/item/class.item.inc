<?php

// public $rev_enabled_cb;  needs to be dropped - use item rev only
class item extends dbObject {

 public static $table_name = "item";
 public static $primary_column = "item_id";
 public static $key_column = 'item_number';
 public static $module = "inv";
// public static $js_fileName = 'modules/inv/item/js/multi_select.js';
 public $account = [
		 "material_ac_id",
		 "material_oh_ac_id",
		 "overhead_ac_id",
		 "resource_ac_id",
		 "osp_ac_id",
		 "expense_ac_id",
		 "sales_ac_id",
		 "cogs_ac_id",
		 "deffered_cogs_ac_id"
 ];
 public $checkbox = [
		 "item_rev_enabled_cb",
		 "inventory_item_cb",
		 "stockable_cb",
		 "transactable_cb",
		 "reservable_cb",
		 "cycle_count_enabled_cb",
		 "equipment_cb",
		 "electronic_format_cb",
		 "rev_enabled_cb",
		 "customer_ordered_cb",
		 "internal_ordered_cb",
		 "shippable_cb",
		 "returnable_cb",
		 "purchased_cb",
		 "use_asl_cb",
		 "bom_enabled_cb",
		 "costing_enabled_cb",
		 "inventory_asset_cb",
		 "build_in_wip_cb",
		 "allow_negative_balance_cb"
 ];
 public $field_a = [
		 "item_id",
		 "org_id",
		 "item_number",
		 "item_description",
		 'product_line',
		 'product_line_percentage',
		 "locator_control",
		 "long_description",
		 "uom_id",
		 "item_type",
		 "item_status",
		 "bom_type",
		 "item_rev_number",
		 "default_cost_group",
		 "lot_uniqueness",
		 "lot_generation",
		 "lot_prefix",
		 "lot_starting_number",
		 "serial_generation",
		 "serial_prefix",
		 "serial_starting_number",
		 "serial_uniqueness",
		 "invoice_matching",
		 "default_buyer",
		 "list_price",
		 "un_number",
		 "hazard_classs",
		 "over_receipt_percentage",
		 "receipt_days_early",
		 "receipt_days_late",
		 "receipt_day_action",
		 "receipt_routing",
		 "weight_uom_id",
		 "weight",
		 "volume_uom_id",
		 "volume",
		 "dimension_uom_id",
		 "length",
		 "width",
		 "height",
		 "planning_method",
		 "planner",
		 "make_buy",
		 'wip_supply_subinventory',
		 'wip_supply_locator',
		 "fix_order_quantity",
		 "fix_days_supply",
		 "fix_lot_multiplier",
		 "minimum_order_quantity",
		 "maximum_order_quantity",
		 'rounding_option',
		 'minmax_min_quantity',
		 'minmax_max_quantity',
		 'minmax_multibin_number',
		 'minmax_multibin_size',
		 'saftey_stock_days',
		 'saftey_stock_quantity',
		 'saftey_stock_percentage',
		 "forecast_method",
		 "forecast_control",
		 "demand_timefence",
		 "planning_timefence",
		 "release_timefence",
		 "pre_processing_lt",
		 "post_processing_lt",
		 "processing_lt",
		 "cumulative_mfg_lt",
		 "cumulative_total_lt",
		 "lt_lot_size",
		 "wip_supply_type",
		 "ef1",
		 "ef2",
		 "atp",
		 "picking_rule",
		 "sourcing_rule_id",
		 "ip_tax_class",
		 "op_tax_class",
		 "ap_payment_term",
		 "ar_payment_term",
		 "ef_id",
		 "created_by",
		 "creation_date",
		 "last_update_by",
		 "last_update_date",
		 "material_ac_id",
		 "material_oh_ac_id",
		 "overhead_ac_id",
		 "resource_ac_id",
		 "osp_ac_id",
		 "expense_ac_id",
		 "sales_ac_id",
		 "cogs_ac_id",
		 "deffered_cogs_ac_id",
		 "item_rev_enabled_cb",
		 "inventory_item_cb",
		 "stockable_cb",
		 "transactable_cb",
		 "reservable_cb",
		 "cycle_count_enabled_cb",
		 "equipment_cb",
		 "electronic_format_cb",
		 "rev_enabled_cb",
		 "customer_ordered_cb",
		 "internal_ordered_cb",
		 "shippable_cb",
		 "returnable_cb",
		 "purchased_cb",
		 "use_asl_cb",
		 "bom_enabled_cb",
		 "costing_enabled_cb",
		 "inventory_asset_cb",
		 "build_in_wip_cb",
		 "allow_negative_balance_cb"
 ];
 public $initial_search = [
		 'item_id',
		 "item_number",
		 "item_status"
 ];
 public $column = [
		 'item_id',
		 "org_id",
		 "item_number",
		 "item_description",
		 "item_type",
		 "uom_id",
		 "item_status",
		 'processing_lt'
 ];
 public $requiredField = [
		 "item_number",
		 "uom_id",
		 "org_id",
		 "item_description",
		 "item_type",
		 "make_buy"];
 public $otherField = [
		 "org.org"
 ];
 public $fields_inForm_notInDataBase = [
		 'item_category',
		 'item_catalog',
		 'item_reference',
		 'item_template',
		 'sourcing_rule',
		 'action',
		 'multibin_minmax_quantity',
		 'overwrite_minmax_min_quantity',
		 'overwrite_minmax_max_quantity',
		 'overwrite_minmax_multibin_number',
		 'overwrite_minmax_multibin_size'
 ];
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
 ];
 public $search_functions = [
		 'Item From' => 'search_item_number_from',
		 'Item To' => 'search_item_number_to',
		 'Organization' => 'search_org_name',
 ];
 public $pageTitle = " Item - Create & Update Items"; //page Title
 public $option_lists = [
		 'item_types' => 'ITEM_TYPE',
		 'item_status' => 'ITEM_STATUS',
		 'planning_method' => 'MP_PLANNING_METHOD',
 ];
 public $prg_minmax_update_parameters = [
		 'Organization' => 'search_org_name',
		 'Min Max Planner ' => 'search_minmax_planner',
		 'Item Number From' => 'search_item_number_from',
		 'Item Number To' => 'search_item_number_to',
		 'Item Id From' => 'search_item_id_from',
		 'Item Id To' => 'search_item_id_to'
 ];
 public $prg_minmax_update_details = [
		 'name' => 'Min Max Attribute Update ',
		 'description' => 'Update Item Attributes related to Min Max ',
 ];
 public $item_id;
 public $org_id;
 public $org;
 public $item_number;
 public $item_description;
 public $product_line;
 public $product_line_percentage;
 public $locator_control;
 public $allow_negative_balance_cb;
 public $long_description;
 public $uom_id;
 public $item_rev_enabled_cb;
 public $item_rev_number;
 public $item_type;
 public $item_status;
 public $inventory_item_cb;
 public $stockable_cb;
 public $transactable_cb;
 public $reservable_cb;
 public $cycle_count_enabled_cb;
 public $bom_enabled_cb;
 public $bom_type;
 public $costing_enabled_cb;
 public $inventory_asset_cb;
 public $default_cost_group;
// public $material_ac;
 public $material_oh_ac;
 public $overhead_ac;
 public $resource_ac;
 public $expense_ac;
 public $osp_ac;
 public $material_ac_id;
 public $material_oh_ac_id;
 public $overhead_ac_id;
 public $resource_ac_id;
 public $expense_ac_id;
 public $osp_ac_id;
 public $lot_uniqueness;
 public $lot_generation;
 public $lot_prefix;
 public $lot_starting_number;
 public $serial_generation;
 public $serial_prefix;
 public $serial_starting_number;
 public $serial_uniqueness;
 public $purchased_cb;
 public $use_asl_cb;
 public $invoice_matching;
 public $default_buyer;
 public $list_price;
 public $un_number;
 public $hazard_classs;
 public $receipt_sub_inventory;
 public $over_receipt_percentage;
 public $over_receipt_action;
 public $receipt_days_early;
 public $receipt_days_late;
 public $receipt_day_action;
 public $receipt_routing;
 public $weight_uom_id;
 public $weight;
 public $volume_uom_id;
 public $volume;
 public $dimension_uom_id;
 public $length;
 public $width;
 public $height;
 public $equipment_cb;
 public $electronic_format_cb;
 public $planning_method;
 public $planner;
 public $make_buy;
 public $wip_supply_locator;
 public $wip_supply_subinventory;
 public $fix_order_quantity;
 public $fix_days_supply;
 public $fix_lot_multiplier;
 public $minimum_order_quantity;
 public $maximum_order_quantity;
 public $saftey_stock_days;
 public $saftey_stock_quantity;
 public $saftey_stock_percentage;
 public $minmax_min_quantity;
 public $minmax_max_quantity;
 public $minmax_multibin_number;
 public $minmax_multibin_size;
 public $rounding_option;
 public $forecast_method;
 public $forecast_control;
 public $demand_timefence;
 public $planning_timefence;
 public $release_timefence;
 public $pre_processing_lt;
 public $post_processing_lt;
 public $processing_lt;
 public $cumulative_mfg_lt;
 public $cumulative_total_lt;
 public $lt_lot_size;
 public $build_in_wip_cb;
 public $wip_supply_type;
 public $customer_ordered_cb;
 public $internal_ordered_cb;
 public $shippable_cb;
 public $returnable_cb;
 public $invoiceable;
 public $op_tax_class;
 public $ip_tax_class;
 public $ap_payment_term;
 public $ar_payment_term;
 public $ef1;
 public $ef2;
 public $atp;
 public $picking_rule;
 public $sourcing_rule_id;
 public $sales_ac;
 public $cogs_ac;
 public $deffered_cogs_ac;
 public $sales_ac_id;
 public $cogs_ac_id;
 public $deffered_cogs_ac_id;
 public $ef_id;
 public $rev_enabled_cb;
 public $rev_number;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $item_category;
 public $item_catalog;
 public $item_reference;
 public $item_template;
 public $action;
 public $multibin_minmax_quantity;
 public $overwrite_minmax_min_quantity;
 public $overwrite_minmax_max_quantity;
 public $overwrite_minmax_multibin_number;
 public $overwrite_minmax_multibin_size;
 public $sourcing_rule;

 Public static function product_line() {
	$option_header = option_header::find_by_name('INV_ITEM_PRODUCT_LINE');
	$ol = option_line::find_by_option_id($option_header->option_header_id);
	return $ol;
 }

 Public static function product_tax_class() {
	$option_header = option_header::find_by_name('INV_ITEM_TAX_CLASS');
	$ol = option_line::find_by_option_id($option_header->option_header_id);
	return $ol;
 }

 Public static function rounding_option() {
	$option_header = option_header::find_by_name('SYS_ROUNDING_OPTION');
	$ol = option_line::find_by_option_id($option_header->option_header_id);
	return $ol;
 }

 Public static function item_types() {
	$option_header = option_header::find_by_name('ITEM_TYPE');
	$coa_account_types = option_line::find_by_option_id($option_header->option_header_id);
	return $coa_account_types;
 }

 Public static function planning_method() {
	$option_header = option_header::find_by_name('MP_PLANNING_METHOD');
	$ol = option_line::find_by_option_id($option_header->option_header_id);
	return $ol;
 }

 Public static function item_status() {
	$option_header = option_header::find_by_name('ITEM_STATUS');
	$coa_account_types = option_line::find_by_option_id($option_header->option_header_id);
	return $coa_account_types;
 }

 Public static function manufacturing_item_types() {
	$option_header = option_header::find_by_name('MANUFACTURING_ITEM_TYPE');
	$mfg_item_types = option_line::find_by_option_id($option_header->option_header_id);
	return $mfg_item_types;
 }

 public function _before_save() {
	if (!empty($this->sourcing_rule)) {
	 $this->sourcing_rule_id = po_sourcing_rule_header::find_by_sourcingRule($this->sourcing_rule)->po_sourcing_rule_header_id;
	}
	if (($this->action == 'update_item_minmax')) {
	 echo "<br> saving minmax details before Item SAVE";
	 $this->_update_item_minmax();
	 return 10;
	}
	if (empty($this->item_id)) {
//before creating item, check if the entered org is a master org or not;
//if the entered org is a master org then create the item else check if item exists in any master org
//items can be created only in master org
	 $org = new org();
	 $is_master_org = false;
	 $all_master_orgs = $org->findAll_item_master();
	 foreach ($all_master_orgs as $master_orgs) {
		if ($master_orgs->org_id == $this->org_id) {
		 $is_master_org = true;
		 return;
		}
	 }
	 if ($is_master_org) {
		return 1;
	 } else {
		//verify if item number exists in master org
		$inv = new inventory();
		$inv_i = $inv->findBy_org_id($this->org_id);
		$item_exists_inItemMaster = $this->findBy_itemNumber_OrgId($inv_i->master_org_id);
		if ($item_exists_inItemMaster) {
		 return 1;
		} else {
		 echo " Items can be created only in master org ";
		 return -99;
		}
	 }
	}
 }

 private function _update_item_minmax() {
	if (empty($this->item_id)) {
	 echo "<br>No Item Id found";
	 return;
	}
	echo "<br>acutal minmax_min_quantity" . $this->minmax_min_quantity;
	if (!empty($this->overwrite_minmax_min_quantity)) {
	 $this->minmax_min_quantity = $this->overwrite_minmax_min_quantity;
	}
	if (!empty($this->overwrite_minmax_max_quantity)) {
	 $this->minmax_max_quantity = $this->overwrite_minmax_max_quantity;
	}
	if (!empty($this->overwrite_minmax_multibin_number)) {
	 $this->minmax_multibin_number = $this->overwrite_minmax_multibin_number;
	}
	if (!empty($this->overwrite_minmax_multibin_size)) {
	 $this->minmax_multibin_size = $this->overwrite_minmax_multibin_size;
	}
	echo "<br>ovwer written minmax_min_quantity" . $this->minmax_min_quantity;
	$item_n = new item();
	$item_n->findBy_id($this->item_id);
	switch ($item_n->rounding_option) {
	 case 'ROUND_UP' :
		$this->multibin_minmax_quantity = ceil($this->multibin_minmax_quantity);
		$this->minmax_multibin_number = ceil($this->minmax_multibin_number);
		$this->minmax_multibin_size = ceil($this->minmax_multibin_size);
		$this->minmax_min_quantity = ceil($this->minmax_min_quantity);
		$this->minmax_max_quantity = ceil($this->minmax_max_quantity);
		break;

	 case 'ROUND_DOWN' :
		$this->multibin_minmax_quantity = floor($this->multibin_minmax_quantity);
		$this->minmax_multibin_number = floor($this->minmax_multibin_number);
		$this->minmax_multibin_size = floor($this->minmax_multibin_size);
		$this->minmax_min_quantity = floor($this->minmax_min_quantity);
		$this->minmax_max_quantity = floor($this->minmax_max_quantity);
		break;

	 case 'ROUND' :
		$this->multibin_minmax_quantity = round($this->multibin_minmax_quantity);
		$this->minmax_multibin_number = round($this->minmax_multibin_number);
		$this->minmax_multibin_size = round($this->minmax_multibin_size);
		$this->minmax_min_quantity = round($this->minmax_min_quantity);
		$this->minmax_max_quantity = round($this->minmax_max_quantity);
		break;

	 case 'default':
		break;
	}
	if ($item_n->planning_method == 'MULTI_MINMAX') {
	 if (!empty($this->overwrite_minmax_min_quantity)) {
		$item_n->minmax_min_quantity = $item_n->minmax_max_quantity = $this->overwrite_minmax_min_quantity;
	 } else {
		$item_n->minmax_min_quantity = $item_n->minmax_max_quantity = $this->multibin_minmax_quantity;
	 }
	 $item_n->minmax_multibin_number = $this->minmax_multibin_number;
	 $item_n->minmax_multibin_size = $this->minmax_multibin_size;
	} else {
	 $item_n->minmax_min_quantity = $this->minmax_min_quantity;
	 $item_n->minmax_max_quantity = $this->minmax_max_quantity;
	 $item_n->minmax_multibin_number = 0;
	 $item_n->minmax_multibin_size = 0;
	}
	$item_n->audit_trial();
	try {
	 $item_n->save();
	 echo "<br>Update of Min Max numbers for " . $item_n->item_number . ' is sucessfully updated ';
	} catch (Exception $e) {
	 echo "<br>Update of Min Max numbers for " . $item_n->item_number . ' is failed!' . $e->getMessage();
	}
	return;
 }

 public function prg_minmax_update($seralized_parameters) {
	$parameters = unserialize($seralized_parameters);
	$this->message = '<br> Starting Min Max Item Updates....<br>';
	$mms = new fp_minmax_suggestion_v();

	if (!empty($parameters['org_id'][0])) {
	 $org_id = $parameters['org_id'][0];
	 $this->message .= '<br> Entered Org Id is : ' . $org_id;
	} else {
	 $this->message .= '<br> Error! : No org id found @ item ' . __LINE__;
	 return $this->message;
	}

	if (!empty($parameters['fp_minmax_header_id'][0])) {
	 $fp_minmax_header_id = $parameters['fp_minmax_header_id'][0];
	 $mms->plan_id = $fp_minmax_header_id;
	 $this->message .= '<br> Entered Min Max Header Id is : ' . $fp_minmax_header_id;
	} else {
	 $this->message .= '<br> Error! : No Min Max Header Id is found @ fp_minmax_header ' . __LINE__;
	 return $this->message;
	}

	if (!empty($parameters['item_id'][0])) {
	 $this->message .= "<br/>Using Min Max Item Update by Item Id ";
	 $item_id = $parameters['item_id'][0];
	 try {
		$mms->item_id = $item_id;
		$mms_i = $mms->findBy_planId_itemId();
		$mm_item = new item();
		foreach ($mms->field_a as $key => $value) {
		 if (property_exists($mm_item, $value)) {
			$mm_item->$value = $mms_i->$value;
		 }
		}
		$mm_item->_update_item_minmax();
		$this->message .= "<br/> Min Max Item Update is sucessfully updated for item_id - " . $item_id .
						' min max header id : ' . $fp_minmax_header_id;
	 } catch (Exception $e) {
		$this->message .= "<br/> Min Max Item Updat fialed for Item id " . $item_id . $e->getMessage();
	 }
	 return $this->message;
	}

	if (!empty($parameters['from_item_id'][0])) {
	 $this->message .= "<br/>Using  Min Max Planner by Item Id Range ";
	 $from_item_id = $parameters['from_item_id'][0];
	 if (!empty($parameters['to_item_id'][0])) {
		$to_item_id = $parameters['to_item_id'][0];
	 } else {
		$to_item_id = $from_item_id;
	 }
	 $item = new item();
	 $item_range = $item->findBy_itemIdRange($from_item_id, $to_item_id);
	 foreach ($item_range as $item_record) {
		$mms->item_id = $item_record->item_id;
		$mms_i = $mms->findBy_planId_itemId();
		$mm_item = new item();
		foreach ($mms->field_a as $key => $value) {
		 if (property_exists($mm_item, $value)) {
			$mm_item->$value = $mms_i->$value;
		 }
		}
		try {
		 $mm_item->_update_item_minmax();
		 $this->message .= "<br>Min Max Item Attributes is sucessfully updated for item_id - " . $mms->plan_id .
						 ' fp_minmax_header_id : ' . $fp_minmax_header_id;
		} catch (Exception $e) {
		 $this->message .= "<br>Min Max Plannerp failed for Item id " . $mms_records->item_id . $e->getMessage();
		}
	 }
	 return $this->message;
	}

	if (!empty($parameters['from_item_number'][0])) {
	 $this->message .= "<br/>Using  Min Max Planner by Item Number Range ";
	 $from_item_number = $parameters['from_item_number'][0];
	 if (!empty($parameters['to_item_number'][0])) {
		$to_item_number = $parameters['to_item_number'][0];
	 } else {
		$to_item_number = $from_item_number;
	 }
	 $item = new item();
	 $item_range = $item->findBy_itemNumberRange_OrgId($from_item_number, $to_item_number, $org_id);
	 foreach ($item_range as $item_record) {
		$mms->item_id = $item_record->item_id;
		$mms_i = $mms->findBy_planId_itemId();
		$mm_item = new item();
		foreach ($mms->field_a as $key => $value) {
		 if (property_exists($mm_item, $value)) {
			$mm_item->$value = $mms_i->$value;
		 }
		}
		try {
		 $mm_item->_update_item_minmax();
		 $this->message .= "<br>Min Max Item Attributes is sucessfully updated for item_id - " . $mms->plan_id .
						 ' fp_minmax_header_id : ' . $fp_minmax_header_id;
		} catch (Exception $e) {
		 $this->message .= "<br>Min Max Plannerp failed for Item id " . $mms_records->item_id . $e->getMessage();
		}
	 }
	 return $this->message;
	}

	//if no item id/number is given
	$this->message .= "<br/>Updating Min Max Attributes for all Items ";
	$mms_all = $mms->findBy_planId();
	foreach ($mms_all as $mms_records) {
	 $mm_item = new item();
	 foreach ($mms->field_a as $key => $value) {
		if (property_exists($mm_item, $value)) {
		 $mm_item->$value = $mms_records->$value;
		}
	 }
	 try {
		$mm_item->_update_item_minmax();
		$this->message .= "<br>Min Max Item Attributes is sucessfully updated for item_id - " . $mms_records->item_id .
						' fp_minmax_header_id : ' . $mms->plan_id;
	 } catch (Exception $e) {
		$this->message .= "<br>Min Max Plannerp failed for Item id " . $mms_records->item_id . $e->getMessage();
	 }
	}
	return $this->message;
 }

 public static function find_item_number_by_item_number($item_number) {
	global $db;
	$sql = "SELECT * FROM "
					. self::$table_name
					. " where item_number LIKE '%{$item_number}%' LIMIT 0, 30";
	$result = $db->query($sql);
	$data = array();
	if ($result && mysql_num_rows($result)) {
	 while ($row = $db->fetch_array($result)) {
		$data[] = array(
				'label' => $row['item_number'],
				'item_number' => $row['item_number'],
				'item_id' => $row['item_id'],
				'description' => $row['item_description'],
				'uom_id' => $row['uom_id']
		);
	 }
	}

	return $data;
 }

 public static function find_by_itemNumber_orgId($item_number, $org_id) {
	global $db;
	$sql = "SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " where item_number LIKE '%{$item_number}%' ";
	$sql .= " AND org_id  = '{$org_id}' ";
	$sql .= " LIMIT 1 ";
	$result = $db->find_by_sql($sql);
	return !(empty($result)) ? array_pop($result) : false;
 }

 public function findAll_ofOrgId($org_id = "") {
	global $db;
	$sql = "SELECT * FROM " . self::$table_name;
	$sql .= " WHERE org_id = :org_id ";
	$param_a = ['org_id'];
	$org_id_i = !empty($org_id) ? $org_id : $this->org_id;
	$value_a = ['org_id' => $org_id_i];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function findAll_minmax_ofOrgId($org_id = "") {
	global $db;
	$sql = "SELECT * FROM " . self::$table_name;
	$sql .= " WHERE org_id = :org_id ";
	$sql .= " AND planning_method = 'MULTI_MINMAX' OR planning_method = 'MINMAX' ";
	$param_a = ['org_id'];
	$org_id_i = !empty($org_id) ? $org_id : $this->org_id;
	$value_a = ['org_id' => $org_id_i];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function findBy_itemNumber_OrgId($org_id = "") {
	global $db;
	$sql = "SELECT * FROM " . self::$table_name;
	$sql .= " where item_number = :item_number ";
	$sql .= " AND org_id = :org_id ";
	$sql .= " LIMIT 1 ";
	$param_a = ['item_number', 'org_id'];
	$org_id_i = !empty($org_id) ? $org_id : $this->org_id;
	$value_a = ['item_number' => $this->item_number, 'org_id' => $org_id_i];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? array_pop($result) : false;
 }

 public function findBy_itemNumberRange_OrgId($item_number1, $item_number2, $org_id = "") {
	global $db;
	$sql = "SELECT * FROM " . self::$table_name;
	$sql .= " where item_number BETWEEN :item_number1 AND  :item_number2";
	$sql .= " AND org_id = :org_id ";
	$param_a = ['item_number1', 'item_number2', 'org_id'];
	$org_id_i = !empty($org_id) ? $org_id : $this->org_id;
	$value_a = ['item_number1' => $item_number1,
			'item_number2' => $item_number2,
			'org_id' => $org_id_i];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function findBy_itemIdRange($item_id1, $item_id2) {
	global $db;
	$sql = " SELECT * FROM " . self::$table_name;
	$sql .= " where item_id BETWEEN :item_id1 AND  :item_id2";
	$param_a = ['item_id1', 'item_id2'];
	$value_a = ['item_id1' => $item_id1, 'item_id2' => $item_id2];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public static function find_all_assigned_orgs($item_number) {
	global $db;
	$sql = "SELECT * FROM " .
					self::$table_name .
					" where item_number= '{$item_number}' ";
	$result = $db->find_by_sql($sql);
	return $result;
 }

 public static function find_all_assigned_org_ids($item_number) {
	global $db;
	$sql = "SELECT org_id FROM " .
					self::$table_name .
					" where item_number= '{$item_number}' ";
	$result = $db->find_by_sql($sql);
	$assigned_inventory_orgs_array = [];

	foreach ($result as $orgs) {
	 $assigned_inventory_orgs_array[] = $orgs->org_id;
	}

	return $assigned_inventory_orgs_array;
 }

 public static function find_item_number_by_itemNumber_OrgId($item_number, $org_id = "") {
	global $db;
	$sql = "SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " where item_number LIKE '%{$item_number}%' ";
	if (!empty($org_id)) {
	 $sql .= " AND org_id  = '{$org_id}' ";
	}
	$result = $db->find_by_sql($sql);
	$data = array();
	foreach ($result as $row) {
	 $data[] = array(
			 'label' => $row->item_number,
			 'item_number' => $row->item_number,
			 'item_id' => $row->item_id,
			 'item_description' => $row->item_description,
			 'uom_id' => $row->uom_id,
			 'processing_lt' => $row->processing_lt
	 );
	}
//	$return_array['jsonvalue'] = $data;

	return $data;
 }

 public function copy($item_id) {
	global $db;
	$sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM item WHERE `item_id` = '{$item_id}' ";
	if ($db->query($sql1)) {
	 $sql2 = "  UPDATE tmptable SET `item_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `item_id` = '{$item_id}' ";
	 if ($db->query($sql2)) {
		$sql3 = " INSERT INTO `item` SELECT * FROM tmptable WHERE `item_id` = '' ";
		if ($db->query($sql3)) {
		 $this->item_id = $db->insert_id();
		 $this->msg = 1;
		} else {
		 $this->msg = 0;
		}
	 }
	}
	return $this->msg;
 }

 public function multi_select_input_fields() {
	$multi_select_input = [
			'overwrite_minmax_min_quantity',
			'overwrite_minmax_max_quantity',
			'overwrite_minmax_multibin_number',
			'overwrite_minmax_multibin_size'
	];
	return $multi_select_input;
 }

 public function multi_select_hidden_fields() {
	$multi_select_hidden = [
			'action_class_name',
			'mode',
			'action',
			'show_block',
	];

	return $multi_select_hidden;
 }

}

//end of item class
?>