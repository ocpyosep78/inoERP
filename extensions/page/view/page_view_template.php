<div id="all_contents">
 <div id="content_left"></div>
<div id="content_right">
 <div id="content_right_left">
  <div id="content_top"></div>
<div id="content">


<div id="structure">
 <div id="pages">
  <div id ="form_header">
   <ul id="form_box"> 
    <li>
     <div id="loading"><img alt="Loading..." src="<?php echo HOME_URL; ?>themes/images/loading.gif"/></div>
    </li>
    <li> 
     <div class="error"></div>
     <?php echo (!empty($show_message)) ? $show_message : ""; ?> 
    </li>
    <?php if (!empty($$class->page_id)) { ?>
     <li>
      <div id="scrollElement">
       <div class="hidden"><input type="hidden" name="page_id" id="page_id" value="<?php echo htmlentities($$class->page_id); ?>"></div>
       <div id="page_element">
        <ul>
         <li><h3> <?php echo htmlentities($$class->subject); ?>" </h3></li>
         <li class="created_by"><?php echo htmlentities($$class->created_by); ?></li>
         <li class="creation_date"><?php echo htmlentities($$class->creation_date); ?></li>
         		<?php if($allow_content_update) { ;?>
					<li><a href="form.php?class_name=page&mode=9&page_id=<?php echo $$class->page_id;?>"><img src="<?php echo HOME_URL; ?>themes/images/edit.png" alt="update" /> </a></li>
					<?php } ;?>
      <div id="contentId"><?php 
//			echo nl2br(base64_decode($$class->content));
     echo ($$class->content_php_cb == 1) ? ino_eval(base64_decode($$class->content)) : nl2br(base64_decode($$class->content));?></div>
       <div id="terms"><label>Tags : </label><?php echo htmlentities($$class->terms); ?></div>
       <div id="attachment_page"><label>Attachments : </label>
        <?php echo (!empty($file_list)) ? $file_list : ""; ?>
       </div>
       <div id="page_navigation">
        <ul>
         <li class="parent_id"><label>Parent : </label>
          <?php echo!(empty($parent_id)) ? $parent_id : "" ?>
         </li>
        </ul>
       </div>
       <div id="comments">
        <div id="comment_list">
         <?php echo!(empty($comments)) ? $comments : ""; ?>
        </div>
        <?php
        $reference_table = 'page';
        $reference_id = $$class->page_id;
        include_once 'comment.php';
        ?>
        <div id="new_comment">
        </div>
       </div>
      </div>  
     </li>
     <?php
    } else {
     echo (!empty($$class_summary_list)) ? $$class_summary_list : "";
    }
    ?>
   </ul>
  </div>
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
