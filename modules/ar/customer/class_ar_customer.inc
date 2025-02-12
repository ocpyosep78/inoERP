<?php

class ar_customer extends dbObject {

 public static $table_name = 'ar_customer';
 public static $dependent_classes = ['ar_customer_site'];
 public static $primary_column = 'ar_customer_id';
 public static $key_column = 'customer_number';
 public static $module = "ar";
 public static $system_info = [
		 'name' => 'Customer',
		 'number' => '1301',
		 'description' => 'Define and mainten external/internal customers',
		 'version' => '1.1.1.3',
		 'db_version' => '1001',
		 'mod_version' => '1.1.x-1.1',
		 'dependent_class' => array('ar_customer_site', 'ar_customer_bu'),
		 'primary_entity_cb' => '',
		 'module_name' => 'ar',
		 'weight' => 1
 ];
 public $field_a = [
		 'ar_customer_id',
		 "customer_number",
		 "customer_name",
		 "supplier_id",
		 "customer_type",
		 "tax_country",
		 "tax_reg_no",
		 "tax_payer_id",
		 "address_id",
		 "customer_contact_id",
		 'customer_credit_class',
		 "ef_id",
		 "status",
		 "rev_enabled_cb",
		 "rev_number",
		 "created_by",
		 "creation_date",
		 "last_update_by",
		 "last_update_date"
 ];
 public $initial_search = [
		 "ar_customer_id",
		 "customer_number",
		 "customer_name",
		 "tax_country"
 ];
 public $column = [
		 "ar_customer_id",
		 "customer_number",
		 "customer_name",
		 "tax_country",
		 "tax_reg_no"
 ];
 public $account = [
 ];
 public $checkbox = [
		 "rev_enabled_cb"
 ];
 public $addressField = [
		 "address_id"
 ];
 public $fields_inForm_notInDataBase = [
		 'header_address_name',
		 'header_address',
		 'header_country',
		 'header_postal_code',
 ];
 public $requiredField = [
		 "customer_number",
		 "customer_name",
		 "tax_country"
 ];
 public $search = [
		 '_update_path' => 'form.php?class_name=ar_customer',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " Customer "; //page Title
 public $option_lists = [
		 'customer_types' => 'AR_CUSTOMER_TYPE',
		 'customer_credit_class' => 'AR_CUSTOMER_CREDIT_CLASS'
 ];
 public $ar_customer_id;
 public $customer_number;
 public $customer_name;
 public $supplier_id;
 public $customer_type;
 public $tax_country;
 public $tax_reg_no;
 public $tax_payer_id;
 public $address_id;
 public $customer_contact_id;
 public $ef_id;
 public $status;
 public $rev_enabled_cb;
 public $rev_number;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $msg;
 public $customer_credit_class;
 public $header_address_name;
 public $header_address;
 public $header_country;
 public $header_postal_code;

 Public static function customer_types() {
	$option_header = option_header::find_by_name('AR_CUSTOMER_TYPE');
	$customer_types = option_line::find_by_option_id($option_header->option_header_id);
	return $customer_types;
 }

 Public static function customer_credit_class() {
	$option_header = option_header::find_by_name('AR_CUSTOMER_CREDIT_CLASS');
	$customer_credit_class = option_line::find_by_option_id($option_header->option_header_id);
	return $customer_credit_class;
 }

 public function _before_showing() {
	$address = new address();
	if (!empty($this->address_id)) {
	 $address->findBy_id($this->address_id);
	 $this->header_address_name = $address->address_name;
	 $this->header_address = $address->address;
	 $this->header_country = $address->country;
	 $this->header_postal_code = $address->postal_code;
	}
 }

 public function findBy_customerName_OrgId($limit = 30) {
	global $db;
	$sql = " SELECT ac.customer_name, ac.ar_customer_id, ac.customer_number ";
	$sql .= " FROM ar_customer ac ";
	$sql .= " RIGHT JOIN ar_customer_bu acu ON  acu.ar_customer_id = ac.ar_customer_id ";
	$sql .= " WHERE  acu.org_id = :org_id ";
	$sql .= " AND  ac.customer_name LIKE :customer_name ";

	$param_a = ['customer_name', 'org_id'];
	$customer_name = '%' . $this->customer_name . '%';
	$value_a = [ 'customer_name' => $customer_name, 'org_id' => $this->org_id];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function findBy_customer_name($limit = 30) {
	global $db;
	$sql = " SELECT * FROM "
					. self::$table_name
					. " where customer_name LIKE :customer_name LIMIT $limit";
	$param_a = ['customer_name'];
	$customer_name = '%' . $this->customer_name . '%';
	$value_a = [ 'customer_name' => $customer_name];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function searchBy_customer_name() {
	$result = $this->findBy_customer_name();
	$data = array();
	if (!empty($result)) {
	 foreach ($result as $obj) {
		$data[] = array(
				'label' => $obj->customer_name,
				'ar_customer_id' => $obj->ar_customer_id,
				'customer_number' => $obj->customer_number
		);
	 }
	}
	return $data;
 }

 public function searchBy_customerName_orgId() {
	$result = $this->findBy_customerName_OrgId();
	$data = array();
	if (!empty($result)) {
	 foreach ($result as $obj) {
		$data[] = array(
				'label' => $obj->customer_name,
				'ar_customer_id' => $obj->ar_customer_id,
				'customer_number' => $obj->customer_number
		);
	 }
	}
	return $data;
 }

 public static function find_customer_number_by_customer_number($customer_number) {
	global $db;
	$sql = "SELECT * FROM "
					. self::$table_name
					. " where customer_number LIKE '%{$customer_number}%' LIMIT 0, 30";
	$result = $db->query($sql);
	$data = array();
	if ($result && mysql_num_rows($result)) {
	 while ($row = $db->fetch_array($result)) {
		$data[] = array(
				'label' => $row['customer_number'],
				'customer_number' => $row['customer_number'],
				'ar_customer_id' => $row['ar_customer_id'],
				'description' => $row['customer_description']
		);
	 }
	}

	return $data;
 }

 public static function find_customer_number_by_customerNumber_OrgId($customer_number, $org_id) {
	global $db;
	$sql = "SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " where customer_number LIKE '%{$customer_number}%' ";
	$sql .= " AND org_id  = '{$org_id}' ";
	$result = $db->query($sql);
	$data = array();
	$return_array = array();
	if ($result && mysql_num_rows($result)) {
	 while ($row = $db->fetch_array($result)) {
		$data[] = array(
				'label' => $row['customer_number'],
				'customer_number' => $row['customer_number'],
				'ar_customer_id' => $row['ar_customer_id'],
				'description' => $row['customer_description']
		);
	 }
	}
	$return_array['jsonvalue'] = $data;

	return $data;
 }

 public static function find_ar_customer_id_from_customerNumber_OrgId($customer_number, $org_id) {
	global $db;
	$sql = "SELECT ar_customer_id FROM " .
					self::$table_name .
					" where customer_number= '{$customer_number}' " .
					" AND org_id= '{$org_id }'" .
					" LIMIT 1";

	$result = $db->query($sql);
	if ($result && mysql_num_rows($result)) {
	 while ($row = $db->fetch_array($result)) {
		$ar_customer_id = $row['ar_customer_id'];
	 }//end of while Loop
	 return $ar_customer_id;
	} else {
	 return false;
	}
 }

 public static function find_by_customerNumber_OrgId($customer_number, $org_id) {
	$ar_customer_id = self::find_ar_customer_id_from_customerNumber_OrgId($customer_number, $org_id);
	$result = self::find_by_id($ar_customer_id);
	return $result;
 }

 public static function find_all_assigned_orgs($ar_customer_id) {
	global $db;
	$sql = "SELECT * FROM " .
					'customer_bu' .
					" where ar_customer_id= '{$ar_customer_id}' ";
	$result = $db->result_array_assoc($sql);
	return $result;
 }

 public static function find_customer_by_customerName($customer_name) {
	global $db;
	$sql = "SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " where customer_name LIKE '%{$customer_name}%' ";

	$result = $db->query($sql);
	$data = array();
	$return_array = array();
	if ($result && mysql_num_rows($result)) {
	 while ($row = $db->fetch_array($result)) {
		$data[] = array(
				'label' => $row['customer_name'],
				'customer_name' => $row['customer_name'],
				'ar_customer_id' => $row['ar_customer_id'],
				'customer_number' => $row['customer_number']
		);
	 }
	}
	$return_array['jsonvalue'] = $data;

	return $data;
 }

 public function copy($ar_customer_id) {
	global $db;
	$sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM customer WHERE `ar_customer_id` = '{$ar_customer_id}' ";
	if ($db->query($sql1)) {
	 $sql2 = "  UPDATE tmptable SET `ar_customer_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `ar_customer_id` = '{$ar_customer_id}' ";
	 if ($db->query($sql2)) {
		$sql3 = " INSERT INTO `customer` SELECT * FROM tmptable WHERE `ar_customer_id` = '' ";
		if ($db->query($sql3)) {
		 $this->ar_customer_id = $db->insert_id();
		 $this->msg = 1;
		} else {
		 $this->msg = 0;
		}
	 }
	}
	return $this->msg;
 }

}

//end of customer class
?>