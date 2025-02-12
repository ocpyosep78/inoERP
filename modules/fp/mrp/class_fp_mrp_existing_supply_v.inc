<?php

class fp_mrp_existing_supply_v extends dbObject {

 public static $table_name = "fp_mrp_existing_supply_v";
 public static $primary_column = "document_id";
 public static $key_column = 'item_id';
 public static $module = "fp";
 public $field_a = [
		 'item_id',
		 'document_type',
		 'quantity',
		 'supply_date',
		 'document_id',
 ];
 public $initial_search = [
		 'item_id',
		 'document_type',
		 'supply_date',
		 'document_id',
 ];
 public $search_functions = [
		 'Organization' => 'search_org_name_onevalue',
		 'MRP Planner ' => 'search_mrp_name_onevalue',
 ];
 public $column = [
		 'item_id',
		 'document_type',
		 'quantity',
		 'supply_date',
		 'document_id',
 ];
 public $search = [
//		 '_show_view_path' => 1,
 ];
 public $pageTitle = " MRP Existing Supply "; //page Title
 public $item_id;
 public $document_type;
 public $quantity;
 public $supply_date;
 public $document_id;

  private function create_fp_mrp_existing_supply_v() {
	$sql = "
CREATE OR REPLACE VIEW fp_mrp_existing_supply_v
(
item_id, document_type, quantity, supply_date, document_id
)
AS
 						SELECT item.item_id as item_id, 'PO' as document_type, 
						(pd.quantity - pd.received_quantity)  as quantity, IFNULL(pd.promise_date, pd.need_by_date) as supply_date,
						pd.po_detail_id as document_id
						FROM item,
						po_line pl,
						po_detail pd,
						po_header ph
						WHERE pl.item_id = item.item_id
						AND pd.po_line_id = pl.po_line_id
						AND pd.po_header_id = ph.po_header_id
						UNION
						SELECT item.item_id as item_id, 'Requisition' as document_type, 
						prd.quantity  as quantity, IFNULL(prd.promise_date, prd.need_by_date) as supply_date,
						prd.po_requisition_detail_id as document_id
						FROM item,
						po_requisition_line prl,
						po_requisition_detail prd,
						po_requisition_header prh
						WHERE prl.item_id = item.item_id
						AND prd.po_requisition_line_id = prl.po_requisition_line_id
						AND prd.po_requisition_header_id = prh.po_requisition_header_id
						AND prd.order_number IS NULL
						UNION
							SELECT item.item_id as item_id, 'Onhand' as document_type, 
							sum(oh.onhand) as quantity, CURDATE() as supply_date,
							oh.onhand_id as document_id
							FROM onhand oh,
               item 
							 WHERE oh.item_id = item.item_id
							GROUP BY oh.item_id
							
           UNION
					 SELECT item.item_id as item_id, 'WO' as document_type,
					 (wwh.nettable_quantity - IFNULL(wwh.completed_quantity,0) - IFNULL(wwh.scrapped_quantity,0))as quantity,
					 wwh.completion_date as supply_date, wwh.wip_wo_header_id as document_id
					 FROM	wip_wo_header wwh,
					 item 
					 WHERE wwh.item_id = item.item_id
";
 }
 
  public function findBy_ItemId($item_id) {
	$sql = " SELECT * FROM " .
					self::$table_name .
					" WHERE item_id= :item_id "
					. " ORDER BY  supply_date ASC ";
	$value_a = ['item_id' => $item_id];
	$result_array = $this->findBySql($sql, $value_a);
	return !empty($result_array) ? $result_array : false;
 }

}

?>
