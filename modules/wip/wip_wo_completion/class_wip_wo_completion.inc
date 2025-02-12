<?php

class wip_wo_completion extends inv_transaction {

 public static $table_name = "inv_transaction";
 public static $primary_column = "inv_transaction_id";
 public static $dependent_classes = ['wip_wo_header'];
 public static $key_column = 'transaction_type_id';
 public static $module = "wo";
 public static $allowed_inv_transactions = [
		 '1' => 'Miscellaneous Issue',
		 '2' => 'Miscellaneous Receipt',
		 '3' => 'Subinventory Transfer'
 ];
 public $field_a = [
		 'inv_transaction_id',
		 'transaction_type_id',
		 'org_id',
		 'status',
		 'receipt_line_id',
		 'item_number',
		 'item_id',
		 'uom_id',
		 'lot_number',
		 'serial_number',
		 'logical_transaction_cb',
		 'document_type',
		 'document_number',
		 'document_id',
		 'wip_wo_bom_id',
		 'po_header_id',
		 'po_line_id',
		 'po_detail_id',
		 'reason',
		 'reference_type',
		 'reference_key_name',
		 'reference_key_value',
		 'description',
		 'from_org_id',
		 'from_subinventory_id',
		 'from_locator_id',
		 'quantity',
		 'from_account_id',
		 'to_org_id',
		 'to_subinventory_id',
		 'to_locator_id',
		 'to_account_id',
		 'unit_cost',
		 'costed_amount',
		 'gl_journal_header_id',
		 'ef_id',
		 'transaction_rev_enabled_cb',
		 'rev_start_number',
		 'created_by',
		 'creation_date',
		 'last_update_by',
		 'last_update_date',
 ];
 //variables used for showing data

 public $initial_search = [
		 "inv_transaction_id",
		 "transaction_type_id",
		 'status',
		 "item_id",
		 "org_id",
		 "item_number",
		 "creation_date",
		 "document_type",
		 "document_number"
 ];
 public $column = [
		 "inv_transaction_id",
		 "transaction_type_id",
		 'status',
		 "item_number",
		 "document_type",
		 "document_number",
		 "reason",
		 "reference",
		 "created_by",
		 "creation_date"];
 public $account = [
		 "from_account_id",
		 "to_account_id",
		 "account_id"];
 public $checkbox = [
		 "logical_transaction_cb",
		 "transaction_rev_enabled_cb"];
 public $fields_inHeader_needsToBeInserted_inPOST = [
		 "org_id",
		 "transaction_type_id"
 ];
 public $requiredField = [
		 "item_number",
		 "uom_id",
		 "quantity",
		 "org_id",
		 "item_id",
		 "transaction_type_id"
 ];
 public $search = [
		 '_show_view_path' => 1,
 ];
 public $pageTitle = " WIP - Create & View WO Completion"; //page Title
 public $option_lists = [
		 'inv_transaction_class' => 'TRANSACTION_TYPE_CLASS'
 ];
 public $fields_inForm_notInDataBase = [
		 "account_id",
		 'item_description',
		 'wip_wo_bom_id',
		 'wip_wo_header_id',
		 'bom_sequence'
 ];
 public $wip_wo_bom_id;
 public $bom_sequence;
 public $wip_wo_header_id;

}

//end of inv_transaction class
?>