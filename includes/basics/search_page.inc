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
			<div class="error"></div><div class="show_loading_small"></div><div id="loading"></div>
			<?php echo (!empty($show_message)) ? $show_message : ""; ?> 
			 </div>
			 <div id="list_contents">
				<div id="searchForm"><?php echo!(empty($search_form)) ? $search_form : ""; ?></div>
				<div id="searchResult">
				 				<?php
				if (!empty($total_count)) {
				 ?>
 				<div id="searchResultMessages">
 				 <ul class="inline_list">
 					<li>
						<?php echo '<h3>Total records : ' . $total_count . '</h3>'; ?>
 					</li>
 					<li id="export_excel_searchResult"> <img src="<?php echo THEME_URL; ?>/images/excel.png" alt="Export to Excel" /></li>
 					<li id="print_searchResult" class="print"> <img src="<?php echo THEME_URL; ?>/images/print.png" alt="Print" /></li>
 					<li id="export_excel_allResult"> <img src="<?php echo THEME_URL; ?>/images/excel_all.png" alt="Export to Excel ALL" /></li>
 				 </ul>
 				</div>
				<?php } ?>
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
				<!--download page creation for all records-->
				<?php
				if (!empty($all_download_sql)) {
				 $search_class_obj_all = option_header::find_by_sql($all_download_sql);
				 $search_class_array_all = json_decode(json_encode($search_class_obj_all), true);
				 ?>
 				<!--download page form-->
 				<form action="<?php echo HOME_URL; ?>download.php" method="POST" name="download_all" id="download_all">
 				 <input type="hidden"  name="data" value="<?php print base64_encode(serialize($search_class_array_all)) ?>" >
 				</form>
 				<!--download page completion-->	 
				<?php }
				?>

				</div>

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
