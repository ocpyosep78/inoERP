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
  <div id="content_right">
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
				<div id="scrollElement">
				 <div id="print">
					<table class="find_page normal">
        <thead> 
          <tr>
            <th>Click Select</th>
            <?php
            foreach ($column_array as $key => $value) {
              echo '<th>' . $value . '</th>';
            }
            ?>
             </tr>
        </thead>

        <?php
        If ($search_result) {
          echo '<tbody>';
          foreach ($search_result as $record) {
            echo '<tr>';
            echo '<td><input type="button" class="quick_select button"
          value="' . $record->$module_info[0]['primary_column'] . '"></td>';
            
            foreach ($column_array as $key => $value) {
              echo '<td>' . $record->$value . '</td>';
            }
            echo '</tr>';
          }
          echo '</tbody>';
        }
        ?>

      </table>
					
				 </div>
				</div>
				
				<div id="pagination" style="clear: both;">
				 <?php echo!(empty($pagination_statement)) ? $pagination_statement : "";
				 ?>
				</div>
			 </div>
			</div>
		 </div>
		</div>
	 </div>
	 	</div>
	 </div>


<?php include_template('footer.inc') ?>
