<?php if (!empty($msg)) {
 $show_message = '<div id="dialog_box">';
  foreach ($msg as $key => $value) {
   $x = $key + 1;
   $show_message .= 'Message ' . $x . ' : ' . $value . '<br />';
  }
 $show_message .= '</div>';
}
?>
<div id="all_contents">
 <div id="content_left"></div>
 <div id="content_right">
	<div id="content_right_left">
	 <div id="content_top"></div>
	 <div id="content">
		<div id="main">
		 <div id="structure">
			<div id="contents">
			 <div id ="form_header">
				<ul id="form_box"> 
				 <li>
					<div id="loading"><img alt="Loading..." src="<?php echo HOME_URL; ?>themes/images/loading.gif"/></div>
				 </li>
				 <li> 
					<div class="error"></div>
					<?php echo (!empty($show_message)) ? $show_message : ""; ?> 
				 </li>
				</ul>
			 </div>
			 <div id="list_contents">
				<div id="searchForm"><?php echo!(empty($search_form)) ? $search_form : ""; ?></div>
				<?php
				if (!empty($total_count)) {
				 echo '<h3>Total records : ' . $total_count . '</h3>';
				}
				?>
				<div id="scrollElement">
				 <div id="print">
					<div id="search_result"> <?php echo!(empty($search_result_statement)) ? $search_result_statement : ""; ?></div>
				 </div>
				</div>
				<div id="pagination" style="clear: both;">
				 <?php echo!(empty($pagination_statement)) ? $pagination_statement : "";
				 ?>
				</div>
				<!--download page creation-->
				<ul class="data_export">
				 <li> <input type="submit" class="download button excel" value="<?php echo $per_page ?> Records" form="download"></li>
				 <li> <input type="submit" class="download button excel" value="All Records" form="download_all"></li>
				 <li> <input type="button" class="download button print" value="Print"></li>
				</ul>

				<?php
				if (!empty($sql)) {
				 $search_class_obj = option_header::find_by_sql($sql);
				 $search_class_array = json_decode(json_encode($search_class_obj), true);
				}
				?>
				<!--download page form-->
				<form action="<?php echo HOME_URL; ?>download.php" method="POST" name="download" id="download">
				 <input type="hidden"  name="data" value="<?php print base64_encode(serialize($search_class_array)) ?>" >

				</form>

				<!--download page creation for all records-->
				<?php
				if (!empty($all_download_sql)) {
				 $search_class_obj_all = option_header::find_by_sql($all_download_sql);
				 $search_class_array_all = json_decode(json_encode($search_class_obj_all), true);
				}
				?>
				<!--download page form-->
				<form action="<?php echo HOME_URL; ?>download.php" method="POST" name="download_all" id="download_all">
				 <input type="hidden"  name="data" value="<?php print base64_encode(serialize($search_class_array_all)) ?>" >
				</form>
				<!--download page completion-->
			 </div>
			</div>
		 </div>
		</div>
	 </div>
	 <div id="content_bottom"></div>
	</div>
	<div id="content_right_right"></div>
 </div>
</div>
<?php include_template('footer.inc') ?>
