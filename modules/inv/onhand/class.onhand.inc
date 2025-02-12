<?php

class onhand extends dbObject {

 protected static $table_name = "onhand";
 protected static $view_name = "onhand_v";
 public static $primary_column = "onhand_id";
 public static $key_column = 'item_id';
 public static $module = "inv";
//  data base variables as stored database column name
 public $field_a = [
		 'onhand_id',
		 'item_id',
		 'org_id',
		 'subinventory_id',
		 'locator_id',
		 'lot_id',
		 'serial_id',
		 'onhand',
		 'reservable_onhand',
		 'transactable_onhand',
		 'lot_status',
		 'serial_status',
		 'uom_id',
		 'secondary_uom_id',
		 'onhand_status',
		 'ef_id',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 public $initial_search = [
		 "org_id",
		 "subinventory_id",
		 "locator_id",
		 "uom_id",
		 "onhand_id",
		 "item_id",
 ];
//variables used for showing data
 public $column = [
		 "item_number",
		 "item_description",
		 "org_name",
		 "subinventory",
		 "locator",
		 "uom",
		 "onhand",
		 "sum_onhand",
		 "onhand_id",
		 "item_id",
 ];
// public static $checkbox_array =["rev_enabled"                                 
//                                 ];

 public static $group_by = ["locator", "subInventory", "inventory"];
 public $sum_onhand;
 public $onhand_id;
 public $item_id;
 public $org_id;
 public $subinventory_id;
 public $locator_id;
 public $lot_id;
 public $item_number;
 public $item_description;
 public $org_name;
 public $subinventory;
 public $locator;
 public $uom_id;
 public $serial_id;
 public $onhand;
 public $reservable_onhand;
 public $transactable_onhand;
 public $lot_status;
 public $serial_status;
 public $uom;
 public $secondary_uom_id;
 public $onhand_status;
 public $ef_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $msg;
 private $_from_org_id;
 private $_from_subinventory_id;
 private $_from_locator_id;
 private $_to_org_id;
 private $_to_subinventory_id;
 private $_to_locator_id;
 private $_transaction_quantity;

 public function setProperty($property, $value) {
	if (property_exists($this, $property)) {
	 switch ($property) {
		case '_show_update_path':
		 $this->$property = !empty($value) ? true : false;

		case '_result':
		 $this->$property = is_array($value) ? $value : false;


		default:
		 $this->$property = $value;
		 break;
	 }
	}
 }

 public static $view_table_line_tr = <<<'VAR'
              <thead> 
               <tr>
                <th>Action</th>
                <th>Inventory</th>
                <th>SubInventory</th>
                <th>Structure</th>
                <th>Locator Id</th>
                <th>Locator </th>
                <th>Alias</th>
                <th>EF Id</th>
                <th>Status</th>
                <th>Rev Enabled</th>
                <th>Rev Number</th>
               </tr>
              </thead>
VAR;

//Public static function onhand_structure() {
//    $option_header = option_header::find_by_name('LOCATOR_STRUCTURE');
//    $onhand_class = option_line::find_by_option_id($option_header->option_id);
//    return $onhand_class;
//  }

 public static function find_all_v() {
	$sql = " SELECT * FROM " . self::$view_name;
	$result = self::find_by_sql($sql);
	return $result;
 }

 private function create_onhand_v() {
	$sql = "CREATE OR REPLACE VIEW onhand_v
(onhand_id, item_number, item_description, org_name, subinventory, locator,
uom_id,onhand, item_id, org_id, subinventory_id, 
locator_id, lot_id, serial_id, reservable_onhand, 
transactable_onhand, lot_status, serial_status,  
secondary_uom_id, onhand_status, ef_id, created_by, 
creation_date, last_update_by, last_update_date)
AS
SELECT onhand.onhand_id, 
item.item_number, item.description, org.org, subinventory.subinventory, locator.locator,
onhand.uom_id,onhand.onhand,
onhand.item_id, onhand.org_id, onhand.subinventory_id, 
onhand.locator_id, onhand.lot_id, onhand.serial_id, onhand.reservable_onhand, 
onhand.transactable_onhand, onhand.lot_status, onhand.serial_status,  
onhand.secondary_uom_id, onhand.onhand_status, onhand.ef_id, onhand.created_by, 
onhand.creation_date, onhand.last_update_by, onhand.last_update_date

FROM onhand 
LEFT JOIN item ON onhand.item_id = item.item_id
LEFT JOIN org ON onhand.org_id = org.org_id
LEFT JOIN subinventory ON onhand.subinventory_id = subinventory.subinventory_id
LEFT JOIN locator ON onhand.locator_id = locator.locator_id
";
 }

 private function _validate_mandatory_fields() {
	if (empty($this->item_id)) {
	 echo "<br>Onhand Update Failed!Error @onhand - Item Id Missing" . __LINE__;
	 return -99;
	} else if (empty($this->_transaction_quantity)) {
	 echo "<br>Onhand Update Failed!Error @onhand - Transaction Quantity Missing" . __LINE__;
	 return -99;
	}
 }

 private function _update_from_onhand() {
	$from_onhand_sql = " SELECT * FROM onhand";
	$from_onhand_sql .= " WHERE item_id = '{$this->item_id}' ";
	$from_onhand_sql .= " AND  	org_id = '{$this->_from_org_id}' ";

	if (!empty($this->_from_subinvenfromry_id)) {
	 $from_onhand_sql .= " AND  	subinvenfromry_id = '{$this->_from_subinvenfromry_id}' ";
	}
	if (!empty($this->_from_locafromr_id)) {
	 $from_onhand_sql .= " AND  	locafromr_id = '{$this->_from_locafromr_id}' ";
	}
	$from_onhand_sql .= " LIMIT 1 ";

	$from_onhand_result_a = $this->findBy_sql($from_onhand_sql);
	$from_onhand_result = array_pop($from_onhand_result_a);
	if ($from_onhand_result) {
	 $this->onhand = $from_onhand_result->onhand - $this->_transaction_quantity;
	 $this->reservable_onhand = $from_onhand_result->reservable_onhand - $this->_transaction_quantity;
	 $this->transactable_onhand = $from_onhand_result->transactable_onhand - $this->_transaction_quantity;
	 $this->onhand_id = $from_onhand_result->onhand_id;
	} else {
	 $this->onhand = -($this->_transaction_quantity);
	 $this->reservable_onhand = -($this->_transaction_quantity);
	 $this->transactable_onhand = -($this->_transaction_quantity);
	 $this->onhand_id = null;
	}
	$this->org_id = $this->_from_org_id;
	$this->subinventory_id = $this->_from_subinventory_id;
	$this->locator_id = $this->_from_locator_id;

	try {
	 $this->audit_trial();
	 $this->save();
	 echo "<br>Onhand is Sucessfully Updated. The onhand Id is " . $this->onhand_id . ' & Onhand Value is ' . $this->onhand;
	 return 1;
	} catch (Exception $e) {
	 echo "<br>Onhand Update Failed <br> Line # " . __LINE__ . '<br>' . $e->getMessage();
	 return -99;
	}
 }
 
 private function _update_to_onhand() {
	$to_onhand_sql = " SELECT *  FROM onhand";
	$to_onhand_sql .= " WHERE item_id = '{$this->item_id}' ";
	$to_onhand_sql .= " AND  	org_id = '{$this->_to_org_id}' ";

	if (!empty($this->_to_subinventory_id)) {
	 $to_onhand_sql .= " AND  	subinventory_id = '{$this->_to_subinventory_id}' ";
	}
	if (!empty($this->_to_locator_id)) {
	 $to_onhand_sql .= " AND  	locator_id = '{$this->_to_locator_id}' ";
	}
	$to_onhand_sql .= " LIMIT 1 ";

	$to_onhand_result_a = $this->findBy_sql($to_onhand_sql);
	$to_onhand_result = array_pop($to_onhand_result_a);
	if ($to_onhand_result) {
	 pa($to_onhand_result);
	 $this->onhand = $to_onhand_result->onhand + $this->_transaction_quantity;
	 $this->reservable_onhand = $to_onhand_result->reservable_onhand + $this->_transaction_quantity;
	 $this->transactable_onhand = $to_onhand_result->transactable_onhand + $this->_transaction_quantity;
	 $this->onhand_id = $to_onhand_result->onhand_id;
	} else {
	 $this->onhand = $this->_transaction_quantity;
	 $this->reservable_onhand = $this->_transaction_quantity;
	 $this->transactable_onhand = $this->_transaction_quantity;
	 $this->onhand_id = null;
	}
	$this->org_id = $this->_to_org_id;
	$this->subinventory_id = $this->_to_subinventory_id;
	$this->locator_id = $this->_to_locator_id;

	try {
	 $this->audit_trial();
	 $this->save();
	 echo "<br>Onhand is Sucessfully Updated. The onhand Id is " . $this->onhand_id . ' & Onhand Value is ' . $this->onhand;
	 return 1;
	} catch (Exception $e) {
	 echo "<br>Onhand Update Failed <br> Line # " . __LINE__ . '<br>' . $e->getMessage();
	 return -99;
	}
 }

 public function updateOnhand() {
//verify all the mandatory fields exists
	$mandatory_fields = $this->_validate_mandatory_fields();
	if ($mandatory_fields < 0) {
	 echo "<br>Mandatort fields are missing <br> Line # : " . __LINE__;
	 return -99;
	}

	//from org transaction update
	if (!empty($this->_from_org_id)) {
	 try {
		$this->_update_from_onhand();
		return 1;
	 } catch (Exception $e) {
		echo "<br>From Onhand Update Failed <br> Line # " . __LINE__ . '<br>' . $e->getMessage();
		return -99;
	 }
	}

	//to org transaction update
	if (!empty($this->_to_org_id)) {
	 try {
		$this->_update_to_onhand();
		return 1;
	 } catch (Exception $e) {
		echo "<br>From Onhand Update Failed <br> Line # " . __LINE__ . '<br>' . $e->getMessage();
		return -99;
	 }
	}

	//with in org transaction update
	if ((!empty($this->org_id)) && (empty($this->_from_org_id)) && (empty($this->_to_org_id))) {
	 if (!empty($this->_from_subinventory_id)) {
		$this->_from_org_id = $this->org_id;
		try {
		 $this->_update_from_onhand();
		 return 1;
		} catch (Exception $e) {
		 echo "<br>From Onhand Update Failed <br> Line # " . __LINE__ . '<br>' . $e->getMessage();
		 return -99;
		}
	 }
	 if (!empty($this->_to_subinventory_id)) {
		$this->_to_org_id = $this->org_id;
		try {
		 $this->_update_to_onhand();
		 return 1;
		} catch (Exception $e) {
		 echo "<br>From Onhand Update Failed <br> Line # " . __LINE__ . '<br>' . $e->getMessage();
		 return -99;
		}
	 }
	}
 }

 public static function onhand_page() {
	echo '<table class="normal"><thead><tr>';
	foreach (self::$field_array as $key => $value) {
	 echo '<th>' . $value . '</th>';
	}
	echo '</tr></thead><tbody>';

	$onhand = self::find_all();
//    echo '<pre>';
//    print_r($onhand);
//    echo '<pre>';
	foreach ($onhand as $record) {
	 echo '<tr>';
	 foreach (self::$field_array as $key => $value) {
		echo '<td>' . $record->$value . '</td>';
	 }
	 echo '</tr>';
	}
	echo ' </tbody> </table>';
 }

}

//end of onhand class
?>