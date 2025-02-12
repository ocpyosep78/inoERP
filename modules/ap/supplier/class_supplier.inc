<?php

class supplier extends dbObject {

 public static $table_name = "supplier";
 public static $dependent_classes = ['supplier_site'];
 public static $primary_column = "supplier_id";
 public static $key_column = 'supplier_name';
 public static $module = "ap";
 public $checkbox = [
		 "rev_enabled_cb"
 ];
 public static $system_info = [
		 'name' => 'Supplier',
		 'number' => '1201',
		 'description' => 'Define and mainten external/internal suppliers',
		 'version' => '1.1.1.3',
		 'db_version' => '1001',
		 'mod_version' => '1.1.x-1.1',
		 'dependent_class' => array('supplier_site', 'supplier_all_v', 'supplier_bu'),
		 'primary_entity_cb' => '',
		 'module_name' => 'ap',
		 'weight' => 1
 ];
 public $field_a = [
		 "supplier_id",
		 "supplier_number",
		 "supplier_name",
		 "customer_id",
		 "supplier_type",
		 "tax_country",
		 "tax_reg_no",
		 "tax_payer_id",
		 "address_id",
		 "supplier_contact_id",
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
		 "supplier_id",
		 "supplier_number",
		 "supplier_name",
		 "tax_country"
 ];
 public $column = [
		 "supplier_id",
		 "supplier_number",
		 "supplier_name",
		 "tax_country",
		 "tax_reg_no"
 ];
 public $numberField = [
		 'supplier_number',
 ];
 public $requiredField = [
		 "supplier_number",
		 "supplier_name",
		 "tax_country"
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
 public $search = [
		 '_update_path' => 'form.php?class_name=supplier',
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " Supplier "; //page Title
 public $option_lists = [
		 'supplier_type' => 'SUPPLIER_TYPE',
 ];
 public $supplier_id;
 public $supplier_number;
 public $supplier_name;
 public $customer_id;
 public $supplier_type;
 public $tax_country;
 public $tax_reg_no;
 public $tax_payer_id;
 public $address_id;
 public $supplier_contact_id;
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
 public $header_address_name;
 public $header_address;
 public $header_country;
 public $header_postal_code;

 Public static function supplier_types() {
	$option_header = option_header::find_by_name('SUPPLIER_TYPE');
	$coa_account_types = option_line::find_by_option_id($option_header->option_header_id);
	return $coa_account_types;
 }

 Public static function ap_invoice_match_level() {
	$option_header = option_header::find_by_name('AP_INVOICE_MATCH_LEVEL');
	$ap_invoice_match_levels = option_line::find_by_option_id($option_header->option_header_id);
	return $ap_invoice_match_levels;
 }

 Public static function po_receipt_routing() {
	$option_header = option_header::find_by_name('PO_RECEIPT_ROUTING');
	$po_receipt_routing = option_line::find_by_option_id($option_header->option_header_id);
	return $po_receipt_routing;
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

 public static function find_by_supplier_number($supplier_number) {
	global $db;
	$sql = "SELECT * FROM "
					. self::$table_name
					. " where supplier_number LIKE '%{$supplier_number}%' LIMIT 0, 30";
	$result = $db->query($sql);
	$data = array();
	if ($result && mysql_num_rows($result)) {
	 while ($row = $db->fetch_array($result)) {
		$data[] = array(
				'label' => $row['supplier_number'],
				'supplier_number' => $row['supplier_number'],
				'supplier_id' => $row['supplier_id'],
				'description' => $row['supplier_description']
		);
	 }
	}

	return $data;
 }

 public static function find_all_assigned_orgs($supplier_id) {
	global $db;
	$sql = "SELECT * FROM " .
					'supplier_bu' .
					" where supplier_id= '{$supplier_id}' ";
	$result = $db->result_array_assoc($sql);
	return $result;
 }

 public function findBy_supplier_name($limit = 30) {
	global $db;
	$sql = " SELECT * FROM "
					. self::$table_name
					. " where supplier_name LIKE :supplier_name LIMIT $limit";
	$param_a = ['supplier_name'];
	$supplier_name = '%' . $this->supplier_name . '%';
	$value_a = [ 'supplier_name' => $supplier_name];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function findBy_supplierName_OrgId($limit = 30) {
	global $db;
//	$sql = " SELECT * FROM supplier_all_v "
//					. " where supplier_name LIKE :supplier_name AND org_id = :org_id "
//					. " LIMIT $limit";
	$sql = " SELECT su.supplier_name, su.supplier_id, su.supplier_number ";
	$sql .= " FROM supplier su ";
	$sql .= " RIGHT JOIN supplier_bu sb ON  sb.supplier_id = su.supplier_id ";
	$sql .= " WHERE  sb.org_id = :org_id ";
	$sql .= " AND  su.supplier_name LIKE :supplier_name ";

	$param_a = ['supplier_name', 'org_id'];
	$supplier_name = '%' . $this->supplier_name . '%';
	$value_a = [ 'supplier_name' => $supplier_name, 'org_id' => $this->org_id];
	$result = $db->findBy_sql($sql, $param_a, $value_a);
	return !(empty($result)) ? $result : false;
 }

 public function searchBy_supplier_name() {
	$result = $this->findBy_supplier_name();
	$data = array();
	if (!empty($result)) {
	 foreach ($result as $obj) {
		$data[] = array(
				'label' => $obj->supplier_name,
				'supplier_id' => $obj->supplier_id,
				'supplier_number' => $obj->supplier_number
		);
	 }
	}
	return $data;
 }

 public function searchBy_supplierName_orgId() {
	$result = $this->findBy_supplierName_OrgId();
	$data = array();
	if (!empty($result)) {
	 foreach ($result as $obj) {
		$data[] = array(
				'label' => $obj->supplier_name,
				'supplier_id' => $obj->supplier_id,
				'supplier_number' => $obj->supplier_number
		);
	 }
	}
	return $data;
 }

 public function copy($supplier_id) {
	global $db;
	$sql1 = " CREATE TEMPORARY TABLE tmptable SELECT * FROM supplier WHERE `supplier_id` = '{$supplier_id}' ";
	if ($db->query($sql1)) {
	 $sql2 = "  UPDATE tmptable SET `supplier_id` = '' ,
           `org_id` = '{$this->org_id}' 
          WHERE `supplier_id` = '{$supplier_id}' ";
	 if ($db->query($sql2)) {
		$sql3 = " INSERT INTO `supplier` SELECT * FROM tmptable WHERE `supplier_id` = '' ";
		if ($db->query($sql3)) {
		 $this->supplier_id = $db->insert_id();
		 $this->msg = 1;
		} else {
		 $this->msg = 0;
		}
	 }
	}
	return $this->msg;
 }

 private function create_supplier_all_v() {

	$sql = "
CREATE OR REPLACE VIEW supplier_all_v
(
supplier_id,supplier_number, supplier_name ,
supplier_site_id, supplier_site_number, supplier_site_name,
 supplier_type, tax_country, created_by,
customer_id, status,
creation_date, last_update_by, last_update_date,
 supplier_bu_id, org_id, liability_account_id,
payable_account_id, payment_discount_account_id, pre_payment_account_id,
site_tax_country, site_tax_reg_no, site_status,
currency, payment_term_id)
AS
SELECT 
su.supplier_id,su.supplier_number, su.supplier_name ,
ss.supplier_site_id, ss.supplier_site_number, ss.supplier_site_name,
 su.supplier_type, su.tax_country, su.created_by,
su.customer_id, su.status,
su.creation_date, su.last_update_by, su.last_update_date,
 sb.supplier_bu_id, sb.org_id, liability_account_id,
payable_account_id, payment_discount_account_id, pre_payment_account_id,
ss.site_tax_country, ss.site_tax_reg_no, ss.status,
ss.currency, ss.payment_term_id

FROM supplier su
LEFT JOIN supplier_site ss ON ss.supplier_id = su.supplier_id
LEFT JOIN supplier_bu sb ON su.supplier_id = sb.supplier_id
";


	$sql = "
CREATE OR REPLACE VIEW po_all_v
(
po_header_id, bu_org_id, po_type, po_number, supplier_id, supplier_site_id, buyer, currency, header_amount, po_status,
payment_term_id,
supplier_name, supplier_number,
supplier_site_name, supplier_site_number,
payment_term, payment_term_description,
po_line_id, line_type, line_number,	item_id, item_description, line_description, line_quantity, unit_price, line_price,
item_number, uom_id, item_status,
po_detail_id, shipment_number, ship_to_id, sub_inventory_id, locator_id, requestor, quantity,
need_by_date, promise_date,
po_received_quantity, po_accepted_quantity, po_delivered_quantity, po_invoiced_quantity, po_paid_quantity,
ship_to_org, created_by, creation_date, last_update_by, last_update_date
)
AS
SELECT 
su.supplier_id,su.supplier_number, su.supplier_name ,
ss.supplier_site_id, ss.supplier_site_number, ss.supplier_site_name,
 su.supplier_type, su.tax_country, su.created_by,
su.customer_id, su.tax_country, su.tax_country, su.status,
su.creation_date, su.last_update_by, su.last_update_date,
 sb.supplier_bu_id, sb.org_id, sb.supplier_id, liability_account_id,
payable_account_id, payment_discount_account_id, pre_payment_account_id,
ss.supplier_id, ss.site_tax_country, ss.site_tax_reg_no, ss.status,
ss.currency, ss.payment_term_id

FROM supplier su
LEFT JOIN supplier_site ss ON ss.supplier_id = su.supplier_id
LEFT JOIN supplier_bu sb ON su.supplier_id = sb.supplier_id
";
 }

}

//end of supplier class
?>