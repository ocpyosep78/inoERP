<?php

class legal extends dbObject {

 public static $table_name = "legal";
 public static $primary_column = "legal_id";
 public static $key_column = 'org_id';
 public static $module = "org";
 public $field_a = [
		 "legal_id",
		 "org_id",
		 "legal_org_type",
		 "registration_number",
		 "place_of_registration",
		 "country_of_registration",
		 "identification_number",
		 "ein_tin_tan",
		 "ledger_id",
		 "balancing_segments",
		 "ef_id",
		 "status",
		 "rev_enabled",
		 "rev_number",
		 "created_by",
		 "creation_date",
		 "last_update_by",
		 "last_update_date"
 ];
 public $initial_search = [
		 "legal_id",
		 "org_id",
		 "org",
		 "description"
 ];
 public $column = [
		 "legal_id",
		 "org_id",
		 "org",
		 "description"
 ];
 public $requiredField = [
		 "org_id"
 ];
 public $search = [
		 '_update_path' => 'form.php?class_name=legal',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
//		 '_view_action_meassge' => 'View',
//		 '_extra_path' => '',
 ];
 public $pageTitle = " Legal Org - Find All Legal Organizations "; //page Title
 public $legal_id;
 public $org;
 public $description;
 public $legal_org_type;
 public $registration_number;
 public $place_of_registration;
 public $country_of_registration;
 public $identification_number;
 public $ein_tin_tan;
 public $ledger_id;
 public $balancing_segments;
 public $ef_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;

 public function __set($name, $value) {
	if (!empty($this->org_id)) {
	 $org = org::find_by_id($this->org_id);
	 switch ($value) {
		case 'org':
		 $this->org = $org->org;
		 break;

		case 'description':
		 $this->description = $org->description;
		 break;

		default:
		 $this->$name = $value;
		 break;
	 }
	} else {
	 $this->$name = $value;
	}
 }

 public static function find_by_orgId($org_id) {
	global $db;
	$sql = "SELECT * FROM " . self::$table_name . " 
      where org_id={$org_id} LIMIT 1";
	$result_array = self::find_by_sql($sql);
	return !empty($result_array) ? array_shift($result_array) : false;
 }

 public function findBy_orgId($org_id = '') {
	if (!empty($org_id)) {
	 $orgid = $org_id;
	} else {
	 $orgid = $this->org_id;
	}
	global $db;
	$sql = " SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " WHERE org_id = :org_id ";
	$sql .= " LIMIT 1 ";
	$value_a = ['org_id' => $orgid];
	$result = $db->findBySql($sql, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 public function _before_showing() {

	if (!empty($this->org_id)) {
	 $org = org::find_by_id($this->org_id);
	 $this->org = $org->org;
	 $this->description = $org->description;
	}

	if (!empty($this->ledger_id)) {
	 $this->balancing_segments = '';
	 $balancing = new gl_ledger_balancing_values;
	 $balancing_details = $balancing->findBy_ledgerId($this->ledger_id);
	 foreach ($balancing_details as $objs) {
		$this->balancing_segments .= $objs->balancing_values . ' , ';
	 }
	}
 }

 public static function search_add_extra_fields(&$arr) {
	$org = new org;
	if (!(is_array($arr))) {
	 return false;
	}
	foreach ($arr as &$obj) {
	 $primary_column = self::$primary_column;
	 if (!empty($obj->$primary_column)) {
		$org_i = $org->findBy_id($obj->$primary_column);
		$obj->org = $org_i->org;
		$obj->description = $org_i->description;
	 }
	}
 }

}

//end of legal class
?>