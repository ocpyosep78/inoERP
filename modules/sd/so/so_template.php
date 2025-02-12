<div id="all_contents">
 <div id="content_left"></div>
 <div id="content_right">
	<div id="content_right_left">
	 <div id="content_top"></div>
	 <div id="content">
		<div id="structure">
		 <div id="so_divId">
			<!--    START OF FORM HEADER-->
			<div class="error"></div><div id="loading"></div>
			<?php echo (!empty($show_message)) ? $show_message : ""; ?> 
			<!--    End of place for showing error messages-->

			<div id ="form_header">
			 <form action=""  method="post" id="so_header"  name="so_header">
				<div id="tabsHeader">
         <ul class="tabMain">
          <li><a href="#tabsHeader-1">Basic Info</a></li>
          <li><a href="#tabsHeader-2">Finance</a></li>
					<li><a href="#tabsHeader-3">Address Details</a></li>
					<li><a href="#tabsHeader-4">Notes</a></li>
					<li><a href="#tabsHeader-5">Attachments</a></li>
					<li><a href="#tabsHeader-6">Actions</a></li>
         </ul>
				 <div class="tabContainer">
					<div id="tabsHeader-1" class="tabContent">
					 <div class="large_shadow_box"> 
						<ul class="column five_column">
						 <li><label><img src="<?php echo HOME_URL; ?>themes/images/serach.png" class="sd_so_header_id select_popup">
							 SO Header Id : </label>
							<?php echo form::text_field('sd_so_header_id', $sd_so_header->sd_so_header_id, '15', '25', '', 'System Number', 'sd_so_header_id', $readonly) ?>
							<a name="show" href="form.php?class_name=sd_so_header" class="show sd_so_header_id">
							 <img src="<?php echo HOME_URL; ?>themes/images/refresh.png"/></a> 
						 </li>
						 <li><label>SO Number : </label>
							<?php echo form::text_field_d('so_number'); ?>
						 </li>
						 <li><label>BU Name(1) : </label>
							<?php echo form::select_field_from_object('bu_org_id', org::find_all_business(), 'org_id', 'org', $sd_so_header->bu_org_id, 'bu_org_id', $readonly, '', ''); ?>
						 </li>
						 <li><label>SO Type(2) : </label>
							<?php echo form::select_field_from_object('so_type', sd_so_header::so_types(), 'option_line_code', 'option_line_value', $sd_so_header->so_type, 'so_type', $readonly, '', ''); ?>
						 </li>
						 <li><label><img src="<?php echo HOME_URL; ?>themes/images/serach.png" class="ar_customer select_popup">
							 Customer Id(3) : </label><?php echo form::text_field_dsrm('ar_customer_id'); ?>
						 </li>
						 <li><label class="auto_complete">Customer Name(3) : </label><?php echo $customer_name_stmt; ?></li>
						 <li><label class="auto_complete">Customer Number : </label><?php echo $customer_number_stmt; ?></li>
						 <li><label>Customer Site(7) : </label>
							<?php
							if ((!empty($customer_site_name_statement))) {
							 echo $customer_site_name_statement;
							} else {
							 ?>
 							<Select name="customer_site_id[]" class="customer_site_id select" id="customer_site_id" >
 							 <option value="" ></option>
 							</select> 
							<?php } ?>
						 </li>
						 <li><label>Ef Id : </label>
							<?php echo form::extra_field($$class->ef_id, '10', $readonly); ?>
						 </li>
						 <li><label>Status : </label>                      
							<span class="button"><?php echo!empty($$class->so_status) ? $$class->so_status : ""; ?></span>
						 </li>
						 <li><label>Revision : </label>
							<?php echo form::checkBox_field('rev_enabled_cb', $$class->rev_enabled_cb, 'rev_enabled_cb', $readonly); ?>
						 </li> 
						 <li><label>Rev Number : </label>
							<?php form::text_field_wid('rev_number'); ?>
						 </li> 
						 <li><label>Sales Person : </label>
							<?php form::text_field_wid('sales_person'); ?>
						 </li> 
						 <li><label>Description : </label>
							<?php form::text_field_wid('description'); ?>
						 </li> 
						</ul>
					 </div>
					</div>
					<div id="tabsHeader-2" class="tabContent">
					 <div> 
						<ul class="column five_column">
						 <li><label>Doc Currency : </label>
							<?php echo form::select_field_from_object('document_currency', option_header::currencies(), 'option_line_code', 'option_line_value', $$class->document_currency, 'document_currency', $readonly, '', '', 1); ?>
						 </li>
						 <li><label>Payment Term : </label>
							<?php $f->text_field_d('payment_term_id'); ?>
						 </li>
						 <li><label>Payment Term Date : </label>
							<?php echo form::date_fieldAnyDay('payment_term_date', $$class->payment_term_date) ?>
						 </li>
						 <li><label>Sales Person : </label>
							<?php $f->text_field_d('sales_person') ?>
						 </li>
						 <li><label>Agreement Start Date : </label>
							<?php echo form::date_field('agreement_start_date', $$class->agreement_start_date) ?>
						 </li>
						 <li><label>Agreement End Date : </label>
							<?php echo form::date_field('agreement_end_date', $$class->agreement_start_date) ?>
						 </li>
						 <li><label>Exchange Rate Type : </label>
							<?php echo form::text_field_d('exchange_rate_type'); ?>
						 </li>
						 <li><label>Exchange Rate : </label>
							<?php form::number_field_d('exchange_rate'); ?>
						 </li>
						 <li><label>Header Amount : </label>
							<?php form::number_field_d('header_amount'); ?>
						 </li>
						 <li><label>Tax Amount : </label>
							<?php form::number_field_d('tax_amount'); ?>
						 </li>
						</ul>
					 </div>
					</div>
					<div id="tabsHeader-3" class="tabContent">
					 <div class="left_half shipto address_details">
						<ul class="column two_column">
						 <li><label><img src="<?php echo HOME_URL; ?>themes/images/serach.png" class="address_popup select_popup clickable">
							 Ship To Site Id : </label>
							<?php $f->text_field_d('ship_to_id','address_id'); ?>
						 </li>
						 <li><label>Address Name : </label><?php $f->text_field_dr('ship_to_address_name', 'address_name'); ?></li>
						 <li><label>Address :</label> <?php $f->text_field_dr('ship_to_address','address'); ?></li>
						 <li><label>Country  : </label> <?php $f->text_field_dr('ship_to_country','country'); ?></li>
						 <li><label>Postal Code  : </label><?php echo $f->text_field_dr('ship_to_postal_code','postal_code'); ?></li>
						</ul>
					 </div> 
					 <div class="right_half billto address_details">
						<ul class="column two_column">
						 <li><label><img src="<?php echo HOME_URL; ?>themes/images/serach.png" class="address_popup select_popup clickable">
							 Bill To Site Id :</label>
							<?php $f->text_field_d('bill_to_id','address_id'); ?>
						 </li>
						 <li><label>Address Name :</label><?php $f->text_field_dr('bill_to_address_name','address_name'); ?> </li>
						 <li><label>Address :</label> <?php $f->text_field_dr('bill_to_address','address'); ?></li>
						 <li><label>Country  : </label> <?php $f->text_field_dr('bill_to_country','country'); ?></li>
						 <li><label>Postal Code  : </label><?php echo $f->text_field_dr('bill_to_postal_code','postal_code'); ?></li>
						</ul>
					 </div> 
					</div>
					<div id="tabsHeader-4" class="tabContent">
					 <div> 
						<div id="comments">
						 <div id="comment_list">
							<?php echo!(empty($comments)) ? $comments : ""; ?>
						 </div>
						 <?php
						 $reference_table = 'sd_so_header_id';
						 $reference_id = $$class->sd_so_header_id;
						 include_once HOME_DIR . '/extensions/comment/comment.php';
						 ?>
						 <div id="new_comment">
						 </div>
						</div>
					 </div>
					</div>
					<div id="tabsHeader-5" class="tabContent">
					 <div> 
						<div id="show_attachment" class="show_attachment">
						 <div id="file_upload_form">
							<ul class="inRow asperWidth">
							 <li><input type="file" id="attachments" class="attachments" name="attachments[]" multiple/></li>
							 <li> <input type="button" value="Attach" form="file_upload" name="attach_submit" id="attach_submit" class="submit button"></li>
							 <li class="show_loading_small"><img alt="Loading..." src="<?php echo HOME_URL; ?>themes/images/small_loading.gif"/></li>
							</ul>
						 </div>
						 <div id="uploaded_file_details"></div>
						 <?php echo file::attachment_statement($file); ?>
						</div>
					 </div>
					</div>

					<div id="tabsHeader-6" class="tabContent">
					 <div> 
						<ul class="column five_column">
						 <li><label>Action</label>
							<?php echo $f->select_field_from_object('sales_action', ar_transaction_header::transaction_action(), 'option_line_code', 'option_line_value', '', 'sales_action', '', '', $readonly); ?>
						 </li>
						 <li id="document_print"><label>Document Print : </label>
							<a class="button" target="_blank"
								 href="po_print.php?sd_so_header_id_id=<?php echo!(empty($$class->sd_so_header_id_id)) ? $$class->sd_so_header_id_id : ""; ?>" >Transaction</a>
						 </li>
						 <li id="document_status"><label>Change Status : </label>
							<?php echo form::select_field_from_object('approval_status', sd_so_header::approval_status(), 'option_line_code', 'option_line_value', $$class->approval_status, 'set_approval_status', $readonly, '', ''); ?>
						 </li>
						 <li id="copy_header"><label>Copy Document : </label>
							<input type="button" class="button" id="copy_docHeader" value="Header">
						 </li>
						 <li id="copy_line"><label></label>
							<input type="button" class="button" id="copy_docLine" value="Lines">
						 </li>
						</ul>

						<div id="comment" class="shoe_comments">
						</div>
					 </div>
					</div>
				 </div>

				</div>
			 </form>
			</div>

			<div id="form_line" class="form_line"><span class="heading">SO Lines & Shipments </span>
			 <form action=""  method="post" id="so_site"  name="sd_so_line">
				<div id="tabsLine">
				 <ul class="tabMain">
					<li><a href="#tabsLine-1">Basic</a></li>
					<li><a href="#tabsLine-2">Other Info</a></li>
					<li><a href="#tabsLine-3">Dates</a></li>
					<li><a href="#tabsLine-4">Notes</a></li>
				 </ul>
				 <div class="tabContainer">
					<div id="tabsLine-1" class="tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr>
							<th>Action</th>
							<th>Line Id</th>
							<th>Line#</th>
							<th>Type</th>
							<th>Shipping Org</th>
							<th>Item Number</th>
							<th>Item Description</th>
							<th>UOM</th>
							<th>Line Status</th>
							<th>Quantity</th>
						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($sd_so_line_object as $sd_so_line) {
							?>         
 						 <tr class="sd_so_line<?php echo $count ?>">
 							<td>    
 							 <ul class="inline_action">
 								<li class="add_row_img"><img  src="<?php echo HOME_URL; ?>themes/images/add.png"  alt="add new line" /></li>
 								<li class="remove_row_img"><img src="<?php echo HOME_URL; ?>themes/images/remove.png" alt="remove this line" /> </li>
 								<li><input type="checkbox" name="line_id_cb" value="<?php echo htmlentities($sd_so_line->item_description); ?>"></li>           
 								<li><?php echo form::hidden_field('sd_so_header_id', $sd_so_header->sd_so_header_id); ?></li>
 								<li><?php echo form::hidden_field('tax_code_value', $$class_second->tax_code_value); ?></li>
 							 </ul>
 							</td>
 							<td><?php form::text_field_wid2sr('sd_so_line_id'); ?></td>
 							<!--<td><?php // form::text_field_wid2s('line_number');                       ?></td>-->
 							<td><?php echo form::text_field('line_number', $$class_second->line_number, '8', '20', 1, 'Auto no', '', $readonly, 'lines_number'); ?></td>
 							<td><?php echo form::select_field_from_object('line_type', sd_so_line::sd_so_line_types(), 'option_line_id', 'option_line_code', $$class_second->line_type, 'line_type', $readonly); ?></td>
 							<td><?php echo $f->select_field_from_object('shipping_org_id', org::find_all_inventory(), 'org_id', 'org', $$class_second->shipping_org_id, '', '', 1, $readonly); ?></td>
 							<td><?php form::text_field_wid2('item_number', 'select_item_number'); ?>
 							 <img src="<?php echo HOME_URL; ?>themes/images/serach.png" class="select_item_number select_popup"></td>
 							<td><?php form::text_field_wid2('item_description'); ?></td>
 							<td><?php
								echo form::select_field_from_object('uom_id', uom::find_all(), 'uom_id', 'uom_name', $$class_second->uom_id, '', '', 'uom_id');
								?></td>
 							<td><?php $f->text_field_wid2r('line_status'); ?></td>
 							<td><?php form::number_field_wid2s('line_quantity'); ?></td>
 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
					 </table>
					</div>
					<div id="tabsLine-2" class="scrollElement tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr><th>Line Id</th>
							<th>Unit Price</th>
							<th>Line Price</th>
							<th>Tax Code</th>
							<th>Tax Amount</th>
							<th>Line Description</th>
							<th>Picked Quantity </th>
							<th>Shipped Quantity</th>
							<th>Ref Doc Type</th>
							<th>Ref Number</th>
						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($sd_so_line_object as $sd_so_line) {
							?>         
 						 <tr class="sd_so_line<?php echo $count ?>">
 							<td><?php form::text_field_wid2sr('sd_so_line_id'); ?></td>
 							<td><?php form::number_field_wid2('unit_price'); ?></td>
 							<td><?php form::number_field_wid2('line_price'); ?></td>
 							<td><?php echo $f->select_field_from_object('tax_code_id', mdm_tax_code::find_all_outTax_by_inv_org_id($$class_second->shipping_org_id), 'mdm_tax_code_id', 'tax_code', $$class_second->tax_code_id, '', 'output_tax') ?></td>
 							<td><?php form::number_field_wid2('tax_amount'); ?></td>
 							<td><?php form::text_field_wid2('line_description'); ?></td>
 							<td><?php form::number_field_wid2sr('picked_quantity'); ?></td>
 							<td><?php form::number_field_wid2sr('shipped_quantity'); ?></td>
 							<td><?php form::text_field_wid2('reference_doc_type'); ?></td>
 							<td><?php form::text_field_wid2('reference_doc_number'); ?></td>
 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
						<!--                  Showing a blank form for new entry-->
					 </table>
					</div>
					<div id="tabsLine-3" class="scrollElement tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr><th>Line Id</th>
							<th>Requested Date</th>
							<th>Promise Date </th>
							<th>Schedule Ship Date</th>
							<th>Actual Ship Date</th>
						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($sd_so_line_object as $sd_so_line) {
							?>         
 						 <tr class="sd_so_line<?php echo $count ?>">
 							<td><?php form::text_field_wid2sr('sd_so_line_id'); ?></td>
 							<td><?php echo $f->date_fieldFromToday('requested_date', $$class_second->requested_date) ?></td>
 							<td><?php echo $f->date_fieldFromToday('promise_date', $$class_second->promise_date) ?></td>
 							<td><?php echo $f->date_fieldFromToday('schedule_ship_date', $$class_second->schedule_ship_date) ?></td>
 							<td><?php echo $f->date_fieldFromToday('actual_ship_date', $$class_second->actual_ship_date, 1) ?></td>
 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
						<!--                  Showing a blank form for new entry-->
					 </table>
					</div>
					<div id="tabsLine-4" class="tabContent">
					 <table class="form_line_data_table">
						<thead> 
						 <tr>
							<th>Comments</th>

						 </tr>
						</thead>
						<tbody class="form_data_line_tbody">
						 <?php
						 $count = 0;
						 foreach ($sd_so_line_object as $sd_so_line) {
							?>         
 						 <tr class="sd_so_line<?php echo $count ?>">
 							<td></td>
 						 </tr>
							<?php
							$count = $count + 1;
						 }
						 ?>
						</tbody>
						<!--                  Showing a blank form for new entry-->

					 </table>
					</div>
				 </div>
				</div>
			 </form>

			</div>

			<!--END OF FORM HEADER-->
		 </div>
		</div>
		<!--   end of structure-->
	 </div>
	 <div id="content_bottom"></div>
	</div>
	<div id="content_right_right"></div>
 </div>

</div>

<?php include_template('footer.inc') ?>
