<?php include_once("../../../includes/basics/basics.inc"); ?>
<?php
if ((!empty($_REQUEST['action'])) && ($_REQUEST['action'] = 'search')) {
 if (empty($_REQUEST['term'])) {
	exit;
 }
 $customer_name = $_REQUEST['term'];
 if (!empty($_REQUEST['primary_column1'])) {
	$primary_column1 = $_REQUEST['primary_column1'];
 }
 $customer = new ar_customer();
 $customer->customer_name = $customer_name;
 if (!empty($primary_column1)) {
	$customer->org_id = $primary_column1;
	$data = $customer->searchBy_customerName_orgId();
 } else {
	$data = $customer->searchBy_customer_name();
 }
// JSON data
 echo json_encode($data);
 flush();

 //return from this file
 return;
}
?>

<div id="customer_bu_addresses">
 <?php
 if ((!empty($_GET['ar_customer_id'])) && (!empty($_GET['org_id']))) {
	$ar_customer_id = $_GET['ar_customer_id'];
	$org_id = $_GET['org_id'];
	$customer_bu_assigment = ar_customer_bu::find_by_orgId_customerId($ar_customer_id, $org_id);
//	echo "<div id=\"bill_to_id\">$customer_bu_assigment->org_billto_id</div>";
//	echo "<div id=\"bill_to_address\">" . address::find_by_id($customer_bu_assigment->org_billto_id)->address_name . "</div>";
//	echo "<div id=\"ship_to_id\">$customer_bu_assigment->org_shipto_id</div>";
//	echo "<div id=\"ship_to_address\">" . address::find_by_id($customer_bu_assigment->org_shipto_id)->address_name . "</div>";
 }
 ?>
</div>

<div id="json_customer_sites_all">
 <?php
	if ((!empty($_GET['ar_customer_id'])) && ($_GET['find_all_sites'] = 1)) {
	 $ar_customer_id = $_GET['ar_customer_id'];
	 if (!empty($_GET['org_id'])) {
		$org_id = $_GET['org_id'];
		$acs = new ar_customer_site();

		if (ar_customer_bu::validate_customerBuAssignment($ar_customer_id, $org_id) == 1) {
		 echo '<div id="json_customerSites_find_all">'.
						 form::select_field_from_object('ar_customer_site_id', $acs->findBy_parentId($ar_customer_id), 'ar_customer_site_id', 'customer_site_name', '', 'ar_customer_site_id')
						 .'</div>';
		 $arcbu = new ar_customer_bu();
		 $arcbu->ar_customer_id = $ar_customer_id;
		 $arcbu->org_id = $org_id;
		 $arcbu_i = $arcbu->findBy_orgId_customerId();
		 echo "<div id='receivable_ac_id'>".coa_combination::find_by_id($arcbu_i->receivable_ac_id)->combination.'</div>';
		} else {
		 echo "<div class=\"errorMsg\">Customer BU Assignment doesn't exists</div>";
		}
	 } else {
		echo form::select_field_from_object('ar_customer_site_id', ar_customer_site::find_all_sitesOfCustomer($ar_customer_id), 'ar_customer_site_id', 'customer_site_name', '', 'ar_customer_site_id');
	 }
	}
	?>
</div>


<!--//customer site details-->
<div id="json_customer_site_details">
 <?php
 if ((!empty($_GET['ar_customer_site_id'])) && ($_GET['find_site_details'] = 1)) {
	$acs = new ar_customer_site();
	$ar_customer_site_id = $_GET['ar_customer_site_id'];
	$customer_site_details = $acs->findBy_id($ar_customer_site_id);
	?>
  <div id = "json_customer_site_currency">
	 <?php echo form::select_field_from_object('document_currency', option_header::currencies(), 'option_line_code', 'option_line_code', $customer_site_details->currency, 'document_currency'); ?>
  </div>
  <div id= "json_customer_site_payment_terms">
	 <?php echo form::select_field_from_object('payment_term_id', payment_term::find_all(), 'payment_term_id', 'payment_term', $customer_site_details->payment_term_id, 'payment_term_id'); ?>
  </div>
 <?php }
 ?>
</div>