<?php

class inosave extends dbc {

 private $_module;
 private $_classname;
 private $_detail_classname;
 private $_key_field;
 private $_primary_column;
 private $_primary_column2;

 public function setProperty($property, $value) {
	if (property_exists($this, $property)) {
	 switch ($property) {
		case '_module':
		 $this->$property = !empty($value) ? $value : 'system';

		case '_primary_column':
		 $this->$property = !empty($value) ? $value : $this->_classname . '_id';

		default:
		 $this->$property = $value;
		 break;
	 }
	}
 }

 private function save_class($class) {
	global $ie;
	$cc = new coa_combination();
	if (!isset($item)) {
	 $item = new item();
	}
	$count = 0;
	$coa_id = 1;
	for ($i = 0; $i < count($_POST[$this->_key_field]); $i++) {
	 $$class = new $class;
	 if (property_exists($$class, 'parent_primary_column')) {
		$parent_primary_column = $class::$parent_primary_column;
		if ((!empty($parent_primary_column)) && (empty($_POST[$parent_primary_column][0]))) {
//		 echo "<br>Existing save as no value of $parent_primary_column found! @inosave ".__LINE__;
		 return;
		}
	 }

	 if (property_exists($$class, 'field_a')) {
		$field_array = $$class->field_a;
	 }
	 if (property_exists($$class, 'notUpdatedFromWebForm')) {
		$field_array = $$class->field_a;
		foreach ($$class->notUpdatedFromWebForm as $key_nu => $valye_nu) {
		 if (($key = array_search($valye_nu, $$class->field_a)) !== false) {
			unset($$class->field_a[$key]);
		 }
		}
	 }

	 foreach ($$class->field_a as $key => $value) {
		if (isset($_POST[$value][$i])) {
		 $$class->$value = $_POST[$value][$i];
		}
	 }
	 //check if its multi action data
	 if (!empty($_POST['multi_action_class'][$i])) {
		$multi_action_class = $_POST['multi_action_class'][$i];
		$multi_action_class_primary_column = $multi_action_class::$primary_column;
		$$class->multi_action_class = $multi_action_class;
		if (property_exists($$class, 'multi_action_class_pc')) {
		 $$class->multi_action_class_pc = $multi_action_class_primary_column;
		} else {
		 $$class->multi_action_class_pc = $multi_action_class_primary_column;
		}
		if (!empty($_POST[$$class->multi_action_class_pc][$i])) {
		 $$class->multi_action_class_pc_value = $_POST[$$class->multi_action_class_pc][$i];
		} else {
		 $$class->multi_action_class_pc_value = null;
		}
	 }

	 //fields in form not in databse is used bring in values from one field and set to another field in _before_save
	 //function
	 if (!empty($$class->fields_inForm_notInDataBase)) {
		foreach ($$class->fields_inForm_notInDataBase as $key => $value) {
		 if (!empty($_POST[$value][$i])) {
			$$class->$value = $_POST[$value][$i];
		 } else {
			$$class->$value = NULL;
		 }
		}
	 }

	 if ((empty($_POST['item_id'][$i])) && (!empty($_POST['item_number'][$i])) && (!empty($_POST['org_id']))) {
		$$class->item_id = $item->findBy_itemNumber_OrgId($_POST['item_number'][$i], $_POST['org_id']);
	 }

	 if (!empty($$class->account)) {
		$ledger_id = !empty($$class->ledger_id) ? $$class->ledger_id : null;
		if (!empty($ledger_id)) {
		 $ledg = new gl_ledger();
		 $ledg_i = $ledg->findBy_id($ledger_id);
		 $ledg->coa_structure_id = $ledg_i->coa_structure_id;
		 $coa = $ledg->find_coa_byLedgerId();
		}
		$cc->coa_id = !empty($coa) ? $coa->coa_id : 1;
		foreach ($$class->account as $key => $value) {
		 if (!empty($_POST[$value][$i])) {
			$cc->combination = $_POST[$value][$i];
			try {
			 $combination_id = $cc->findIdBy_combination_coaId();
			 $$class->$value = $combination_id;
			} catch (Exception $e) {
			 echo "<br> Error @inoSaveL76: Invalid account" . $e->getMessage();
			 return;
			}
		 }
		}
	 }

	 if (!empty($$class->dateFields)) {
		foreach ($$class->dateFields as $key => $value) {
		 if (!empty($_POST[$value][$i])) {
			$$class->$value = date('Y-m-d', strtotime($_POST[$value][$i]));
		 } else {
			$$class->$value = NUll;
		 }
		}
	 }

	 //to be removed use numberField
	 if (!empty($$class->number_fields)) {
		foreach ($$class->number_fields as $key => $value) {
		 if (!empty($_POST[$value][$i])) {
			$$class->$value = str_replace(array(','), '', $_POST[$value][$i]);
		 } else {
			$$class->$value = NUll;
		 }
		}
	 }

	 if (!empty($$class->numberField)) {
		foreach ($$class->numberField as $key => $value) {
		 if (isset($_POST[$value][$i])) {
			$$class->$value = str_replace(array(','), '', $_POST[$value][$i]);
		 } else {
			$$class->$value = NUll;
		 }
		}
	 }


	 if (!empty($$class->fields_inHeader_needsToBeInserted_inPOST)) {
		foreach ($$class->fields_inHeader_needsToBeInserted_inPOST as $key => $value) {
		 if (!empty($_POST[$value][$i])) {
			$$class->$value = mysql_prep($_POST[$value][$i]);
		 } else {
			$$class->$value = $_POST[$value][0];
		 }
		}
	 }

	 if (!empty($$class->base_encoded_array)) {
		foreach ($$class->base_encoded_array as $key => $value) {
		 if (!empty($_POST[$value][$i])) {
			$$class->$value = base64_encode($_POST[$value][$i]);
		 } else {
			$$class->$value = "";
		 }
		}
	 }

	 if (!empty($$class->checkbox)) {
		foreach ($$class->checkbox as $key => $value) {
		 if (isset($value)) {
			$valueCount = $value;
		 } else {
			$valueCount = $value . $count;
		 }
		 if (isset($_POST[$valueCount])) {
			$$class->$value = 1;
		 } else {
			$$class->$value = 0;
		 }
		 unset($value);
		}
	 }


	 if (!empty($_POST['file_id_values'])) {
		$$class->file_id_values = $_POST['file_id_values'];
	 }

	 if (!empty($_POST['category_id'])) {
		$posted_category_ids = array();
		foreach ($_POST['category_id'] as $records) {
		 $posted_category_ids[] = $records;
		}
		if ($class == 'content_type') {
		 $category_reference_type = "1";
		} else {
		 $category_reference_type = "2";
		}
	 }

	 //use before save instaed of before submit
	 if (method_exists($$class, '_before_submit')) {
		$$class->_before_submit();
	 }

	 /* if before save is less than zero then exist save
		* if its -99 then show the error message else exist w/o showing any error
		* 10 means all the data are update and leave save.
		* Normall return (1,2 or w/o value), completes the after save and then proceed to save
		*/

	 if (method_exists($$class, '_before_save')) {
		$before_save_result = $$class->_before_save();
		if ($before_save_result < 0) {
		 if ($before_save_result == -99) {
			echo "<br> This action is not allowed " . $class . ' : _before_save() ';
		 }
		 return;
		} else if ($before_save_result == 10) {
		 echo "<br> All data are sucessfully saved @ before save "; //before save completed all activities
		 return;
		}
	 }

	 $time = time();
	 $$class->creation_date = strftime("%Y-%m-%d %H:%M:%S", $time);
	 if ((isset($_SESSION)) && (!empty($_SESSION['username']))) {
		$$class->created_by = $_SESSION['username'];
	 } else {
		$$class->created_by = 'selfWeb';
	 }
	 $$class->last_update_date = $$class->creation_date;
	 $$class->last_update_by = $$class->created_by;
//  echo "<br> in Save";	 pa($$class);
	 $required_field_flag = true;
	 foreach ($$class->requiredField as $key => $value) {
		$required_field_flag = $required_field_flag && (isset($$class->$value));
		if (!isset($$class->$value)) {
//		 pa($$class);
		 echo "<div class='message'> Mandatory $value is missing </div> ";
		 $error = [ 'Mandatory field is missing!' => "$value is NULL"];
		 array_push($ie->page_exception, $error);
		}
	 }

//pa($$class);
	 if ($required_field_flag) {
		try {
		 $result = $$class->save_onWebForm();
		 $error = [ 'Save result :!' => $result];
		 array_push($ie->message, $error);
		 $new_entry = true;
		} catch (Exception $e) {
		 $new_entry = false;
		 echo "<br> Save failed!! error@inosavel line " . __LINE__ . '<br>' . $e->getMessage();
		}
		if ($new_entry) {
		 if (method_exists($$class, '_after_save')) {
			$$class->_after_save();
		 }
		 if ((!(empty($$class->file_id_values))) && (count($$class->file_id_values) > 0)) {
			foreach ($$class->file_id_values as $keys => $values) {
			 $file_reference = new file_reference;
			 $file_reference->file_id = $values;
			 $file_reference->status = 'show';
			 $file_reference->reference_table = $class;
			 $file_reference->reference_id = $$class->{$class::$primary_column};
			 $file_reference->save_onWebForm();
			}
		 }
//delete files
		 if (!empty($_POST['delete_file'])) {
			 $fr = new file_reference();
			foreach ($_POST['delete_file'] as $key => $file_reference_id) {
		 $fr->file_reference_id = $file_reference_id;
			 $fr->delete();
			}
		 }
//hide files..change status to hide
		 if (!empty($_POST['[hide_file'])) {
			foreach ($_POST['[hide_file'] as $key => $file_reference_id) {
			 $file_ref = file_reference::find_by_id($file_reference_id);
			 $file_reference = new file_reference;
			 foreach (file_reference::$field_array as $key => $value) {
				if (!empty($file_ref->$value)) {
				 $file_reference->$value = $file_ref->$value;
				}
			 }
			 $file_reference->status = 'hide';
			}
			$file_reference->save_onWebForm();
		 }

//     add Categories in categoegory reference table
		 if ((!(empty($posted_category_ids))) && ($class != 'category') && (count($posted_category_ids) > 0)) {
			foreach ($posted_category_ids as $keys => $values) {
			 if (!empty($values)) {
				$category_reference = new category_reference;
				$category_reference->major_category_id = category::find_major_category_id($values);
				$category_reference->category_id = $values;
				$category_reference->reference_type = $category_reference_type;
				$category_reference->reference_table = $class;
				$category_reference->reference_id = $$class->{$class::$primary_column};
				$check_category = category_reference::check_majorCategory_in_categoryReference($category_reference->major_category_id, $class, $category_reference->reference_id);

				if (($check_category)) {
				 $category_reference->category_reference_id = $check_category->category_reference_id;
				} else {
				 $category_reference->category_reference_id = "";
				}
				if ($values == 'remove') {
				 $category_reference->delete($category_reference->category_reference_id);
				} else {
				 $category_reference->save_onWebForm();
				}
			 }
			}
		 }
		}//end of after save functions
	 } else {
		$error = [ 'Input Error!' => 'Mandatory Fields are missing. '];
		array_push($ie->page_exception, $error);
	 }
	 $count++;
	}
	return $$class;
//  complete of for loop
 }

 private function save_header() {
	echo '<div id="json_save_header">';
	$class = $this->_classname;
	$keyField = $this->_key_field;
	$primaryColumn = $this->_primary_column;
	$primaryColumn2 = $this->_primary_column2;
	$postArray = get_postArray_From_jqSearializedArray($_POST['headerData']);
	$_POST = $postArray;
//	if ($class == 'user') {
//	 $_POST = $$class->user_verification_update($_POST);
//	}

	if (!empty($_POST)) {
	 $$class = $this->save_class($class);
	}


	if ((!empty($$class)) && (count($$class) > 1)) {
	 echo '<div class="message">Data is sucessfully saved! </div>';
	 echo '<ul id="linids">';
	 foreach ($$class as $array) {
		echo '<li class="' . $array->$keyField . '">' . $array->$primaryColumn . '</li>';
	 }
	 echo '</ul>';
	} elseif (!empty($$class->$primaryColumn)) {
	 echo '<div class="message">Data is sucessfully saved!  ' . $primaryColumn . ' is </div> ';
	 echo '<div id="headerId">' . $$class->$primaryColumn . '</div>';
	 if (!empty($primaryColumn2)) {
		echo '<div id="headerId2">' . $$class->$primaryColumn2 . '</div>';
	 }
	} else {
	 global $ie_array_page;
	 global $ie;
	 echo '<div class="message"> Action Completed - Inosave02! </div> ';
	 if (!empty($ie_array_page)) {
		echo $ie->show_pageErrors($ie_array_page);
	 }
	}

	echo '</div>';
 }

 private function save_line($linedata) {
	echo '<div id="json_save_line">';
	$class = $this->_classname;
	$keyField = $this->_key_field;
	$primaryColumn = $this->_primary_column;
	$postArray = get_postArray_From_jqSearializedArray($linedata);
	$_POST = $postArray;
//	echo 'key $class '.$class . '<pre>'; print_r($_POST);
	if ((!empty($_POST[$keyField])) && (!empty($_POST[$keyField][0]))) {
	 $$class = $this->save_class($class);

	 if (empty($$class)) {
		return;
	 }

	 $$primaryColumn = $$class->$primaryColumn;
	 if ((!empty($$class)) && (count($$class) > 1)) {
		echo '<div class="message">Data is sucessfully saved! </div>';
		echo '<ul id="linids">';
		foreach ($$class as $array) {
		 echo '<li class="' . $array->$keyField . '">' . $array->$primaryColumn . '</li>';
		}
		echo '</ul>';
	 } elseif (!empty($$class->$primaryColumn)) {
		echo '<div class="message">Line Data is sucessfully saved! </div>';
		echo '<div id="lineId">' . $$class->$primaryColumn . '</div>';
	 } else {
		global $ie_array_page;
		global $ie;
		echo '<div class="message"> Error Code - Inosave03! </div> ';
		if (!empty($ie_array_page)) {
		 echo $ie->show_pageErrors($ie_array_page);
		}
	 }
	}
	echo '</div>';
 }

 //function to save both line & detail data
 private function save_line_withDetails($lineDetail_data) {
	echo '<div id="json_save_line">';
	$class = $this->_classname;
	$keyField = $this->_key_field;
	$primaryColumn = $this->_primary_column;
	$detail_classname = $this->_detail_classname;
	$keyField2 = $detail_classname::$key_column;
	$primaryColumn2 = $detail_classname::$primary_column;
	if (!empty($lineDetail_data['lineData'])) {
	 $linedata = $_POST['lineData'];
	 if (!empty($linedata)) {
		$postArray = get_postArray_From_jqSearializedArray($linedata);

		if (!empty($lineDetail_data['detailData'])) {
		 $_posted_detail_line = $_POST['detailData'];
		}

		$_POST = $postArray;
		if ((!empty($_POST[$keyField])) && (!empty($_POST[$keyField][0]))) {
		 $$class = $this->save_class($class);
		 if (!empty($$class->$primaryColumn)) {
			$$primaryColumn = $$class->$primaryColumn;
		 }

		 if ((!empty($$class)) && (count($$class) > 1)) {
			echo '<div class="message">Data is sucessfully saved! </div>';
			echo '<ul id="linids">';
			foreach ($$class as $array) {
			 echo '<li class="' . $array->$keyField . '">' . $array->$primaryColumn . '</li>';
			}
			echo '</ul>';
		 } elseif (!empty($$class->$primaryColumn)) {
			echo '<div class="message">Data is sucessfully saved! </div>';
			echo '<div id="lineId">' . $$class->$primaryColumn . '</div>';
		 } else {
			echo ' Error code:  ! ';
		 }
		}

		if (!empty($_posted_detail_line)) {
		 $postDetailArray = get_postArray_From_jqSearializedArray($_posted_detail_line);
		 $_POST = $postDetailArray;

		 if ((!empty($_POST[$keyField2])) && (!empty($_POST[$keyField2][0]))) {
			$detail_lineID_array = [];
			if (!empty($$class->$primaryColumn)) {
			 array_push($detail_lineID_array, $$class->$primaryColumn);
			}
			$_POST[$primaryColumn] = $detail_lineID_array;
			$this->_key_field = $keyField2;
			$$detail_classname = $this->save_class($detail_classname);
//
//			if ((count($$detail_classname)) > 0) {
//			 pa($$detail_classname);
//			 echo '<div class="message">Detail line is sucessfully saved! </div>';
//			 foreach ($$detail_classname as $details) {
//				if ($key != $detail_classname) {
//				 echo '<div class="option_detailId">' . $details->$primaryColumn2 . '</div>';
//				}
//			 }
//			} else {
//			 global $ie_array_page;
//			 global $ie;
//			 echo '<div class="message"> Error Code - inoSave03! </div> ';
//			 if (!empty($ie_array_page)) {
//				echo $ie->show_pageErrors($ie_array_page);
//			 }
//			}
		 }
		}
	 }
	}
	echo '</div>';
 }

 public function json_save() {
	if (!empty($_POST['headerData'])) {
	 $this->save_header();
	}
	if (!empty($_POST['detail_classname'])) {
	 $this->save_line_withDetails($_POST);
	} else if (!empty($_POST['lineData'])) {
	 $linedata = $_POST['lineData'];
	 $this->save_line($linedata);
	}

	if (!empty($_POST['lineData2'])) {
	 $linedata = $_POST['lineData2'];
	 $this->save_line($linedata);
	}
 }

}

//end of forma class
?>