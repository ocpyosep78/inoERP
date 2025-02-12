$(document).ready(function() {
  $('#loading').hide();
//hiding the loader
var $loader = $('#loading'), timer;
$loader.hide().ajaxStart(function()
    {
        timer && clearTimeout(timer);
        timer = setTimeout(function()
        {
            $loader.show();
        },
        10000);
    }).ajaxStop(function()
    {
        clearTimeout(timer);
        $loader.hide();
    });
    
//creating tabs
$(function() {
    $( "#tabsHeader" ).tabs();
    $( "#tabsLine" ).tabs();
  });
  
//Refresh the content
$('.refresh').click(function() {
    location.reload(true);
});

//get table fields

function select_tableName(){
$(".all_table_names").blur(function() {
var tableName = $(this).val();
var parentId = $(this).parent().parent().attr("id");
getFieldNames(tableName, parentId);
});
}
select_tableName();

function getFieldNames(tableName, parentId) {
 $('#loading').show();
 $.ajax({
  url: 'json.view.php',
  data: {tableName: tableName,
  get_fieldName: 1},
  type: 'get'
 }).done(function(result) {
  var div = $(result).filter('div#json_filed_names').html();
//	$("#" + parentId + " .table_fields").replaceWith('<div class="table_fields"></div>');
  $("#" + parentId + " .table_fields").replaceWith(div);
   $('#loading').hide();
 }).fail(function() {
  alert("table field loading failed");
  $('#loading').hide();
 });
 $(".table_fields").attr("disabled", false);
}

function remove_option(){
$(".remove_option").click(function() {
$(this).closest('li').remove();
});
}
remove_option();

function remove_table(){
$(".remove_table").click(function() {
$(this).closest('ul').remove();
});
}
remove_table();

var objectCount = 1000;
function click_add_new_table(){
$(".add_new_table").on("click",function() {
  $("ul#display_records0").clone().attr("id", "new_object" + objectCount).appendTo($("#display_div"));
  $("#new_object" + objectCount + " .table_fields option").replaceWith("");
  objectCount++;
  select_tableName();
	click_add_new_field();
	
  remove_table();
	remove_option();
	click_add_new_table();
});  
}

click_add_new_table();

var objectCount1 = 10;
function click_add_new_field(){
$(".add_new_field").on("click",function() {
  $(this).closest("ul").children("#field_records0").clone().attr("id", "new_object" + objectCount1).appendTo($(this).parent());
  objectCount1++;
  select_tableName();
//	click_add_new_field();
  remove_table();
	remove_option();
});  
}

click_add_new_field();
//end of get tables

//condition
function condition_operator_type_selection(){
$(".condition_operator_type").blur(function() {
var conditionValue = $(this).val();
if(conditionValue == 'database'){
$(this).closest("td").next(".condition_row_value").children(".condition_row_value_input").remove();
}else if(conditionValue == 'remove'){
$(this).closest("tr").remove();
}else{
var InputText='<input type="text" class="condition_row_value_input input">';
$(this).closest("td").next(".condition_row_value").html(InputText);
}
});
}
condition_operator_type_selection(); 


//allow to drag & drop
function remove_from_dragged_element(){
$(".draggable_element.ui-draggable").dblclick(function() {
$(this).remove();
});
}

function drag_drop_condition(){
$(".draggable_element").draggable(
				{helper:'clone'},
        {cursor: "crosshair" });
		$(".condition_row_parameter").droppable({
			accept: ".draggable_element",
			drop: function(event,ui){
					console.log("Item was Dropped");
					$(this).append($(ui.draggable).clone());
					remove_from_dragged_element();
									}
		});
}
function drag_drop_condition_value(){
$(".draggable_element").draggable(
				{helper:'clone'},
        {cursor: "crosshair" });
		$(".condition_row_value").droppable({
			accept: ".draggable_element",
			drop: function(event,ui){
					console.log("Item was Dropped");
					$(this).append($(ui.draggable).clone());
					remove_from_dragged_element();
									}
		});
}

function drag_drop_condition_sort(){
$(".draggable_element").draggable(
				{helper:'clone'},
        {cursor: "crosshair" });
		$(".sort_fields_field_value").droppable({
			accept: ".draggable_element",
			drop: function(event,ui){
					console.log("Item was Dropped");
					$(this).append($(ui.draggable).clone());
					remove_from_dragged_element();
									}
		});
}
drag_drop_condition();
drag_drop_condition_value();
drag_drop_condition_sort();
remove_from_dragged_element();

var objectCount2 = 500;
function click_add_new_condition(){
$(".add_new_conditions").on("click",function() {
  $("tr.condition_row").clone().appendTo($("table#condition_buttons_table tbody"));
  objectCount1++;
    select_tableName();
//	click_add_new_field();
  remove_table();
	remove_option();
	drag_drop_condition();
drag_drop_condition_value();
drag_drop_condition_sort();
remove_from_dragged_element();
condition_operator_type_selection();
});  
}

click_add_new_condition();

var objectCount2 = 1500;
function click_add_new_sort_criteria(){
$(".add_new_sort_criteria").on("click",function() {
  $("tr.sort_fields_row").clone().appendTo($("table#sort_fields_table tbody"));
  objectCount1++;
    select_tableName();
//	click_add_new_field();
  remove_table();
	remove_option();
	drag_drop_condition();
drag_drop_condition_value();
drag_drop_condition_sort();
remove_from_dragged_element();
condition_operator_type_selection();
});  
}

click_add_new_sort_criteria();



//create the SQL query
//function create_sql_query(){
//tableArray = [];
//$(".all_table_names option:selected").each(function(){
//tableName=$(this).val();
//tableArray.push(tableName);
//});
//fieldArray = [];
//$(".table_fields option:selected").each(function(){
//tableName = $(this).closest("ul").children("#table_records").children(".all_table_names").val();
//fieldTableName=tableName+'.'+$(this).val();
//fieldArray.push(fieldTableName);
//});
//
//whereClauseArray = [];
//$(".condition_row").each(function(){
//var parameter = $(this).find(".condition_buttons").val();
//var operator = $(this).find(".condition_operator").val();
//var operator_type = $(this).find(".condition_operator").val();
//if(operator_type =='database')
//{
//var valueClass="condition_buttons";
//}else{
//var valueClass="condition_row_value_input";
//}
//var value = $(this).find('.' + valueClass).val();
//var whereClause = parameter + " " + operator + " " + value;
//whereClauseArray.push(whereClause);
//});
//
//alert(whereClauseArray);
//
//sql = "SELECT " + fieldArray + "\nFROM \n " + tableArray + "\n WHERE" + whereClauseArray ;
//
//$("#sql_query").val(sql);
//}

function create_sql_query(){
tableArray = [];
$(".all_table_names option:selected").each(function(){
tableName=$(this).val();
tableArray.push(tableName);
});

show_fieldArray = [];
$("#show_field_buttons .showField_buttons").each(function(){
fieldName=$(this).val();
show_fieldArray.push(fieldName);
});

fieldArray = [];
$(".table_fields option:selected").each(function(){
tableName = $(this).closest("ul").children("#table_records").children(".all_table_names").val();
fieldTableName=tableName+'.'+$(this).val();
fieldArray.push(fieldTableName);
});

whereClauseArray = [];
$(".condition_row").each(function(){
var parameter = $(this).find(".condition_buttons").val();
var operator = $(this).find(".condition_operator").val();
var operator_type = $(this).find(".condition_operator_type").val();
if(operator_type =='database')
{
var valueClass="condition_buttons";
var value = $(this).find(".condition_row_value").children().children().val();
}else{
var valueClass="condition_row_value_input";
var value = $(this).find('.' + valueClass).val();
}

sortArray = [];
$(".sort_fields_row").each(function(){
sortFieldName = $(this).find(".showField_buttons").val();
sortFieldValue= $(this).find(".sort_fields_values").val();
if((sortFieldName) && (sortFieldName.length > 0)){
sortField = sortFieldName + " " + sortFieldValue;
sortArray.push(sortField);
}
});

if(parameter){
var whereClause = parameter + " " + operator + " " +'\'' + value + '\'';
whereClauseArray.push(whereClause);
}
});

if(whereClauseArray){
whereClauseArray2 = whereClauseArray.join("\nAND ");
}

var sql="";
if((show_fieldArray) && (show_fieldArray.length > 0) &&(tableArray) && (tableArray.length > 0)){
sql = "SELECT " + show_fieldArray + "\nFROM \n" + tableArray ; 
}
if((whereClauseArray2) && (whereClauseArray2.length > 0)){
 sql += "\nWHERE " + whereClauseArray2 ;
}

if((sortArray) && (sortArray.length > 0)){
sql += "\nORDER BY " + sortArray ;
}

if(sql){
$("#sql_query").val(sql);
alert(sql);
}
}

create_sql_query();

function update_conditions(){
 var condition_buttons = "";
 var showField_buttons = "";
$(fieldArray).each(function(index){
 condition_buttons +='<div class="draggable_element">';
 condition_buttons +='<input type="text" value="' + fieldArray[index]+ '" class="condition_buttons '+fieldArray[index]+'">';
condition_buttons +='</div>';
});
$(fieldArray).each(function(index){
 showField_buttons +='<div class="draggable_element">';
 showField_buttons +='<input type="text" value="' + fieldArray[index]+ '" class="showField_buttons '+fieldArray[index]+'">';
 showField_buttons +='</div>';
});
$("#condition_buttons_div").html(condition_buttons);
$("#show_field_buttons").html(showField_buttons);
}

$("#save_tables").click(function(){
create_sql_query();
update_conditions();
drag_drop_condition();
drag_drop_condition_value();
drag_drop_condition_sort();
condition_operator_type_selection();
remove_from_dragged_element();
});

$("#save_query").click(function(){
create_sql_query();
//update_conditions();
//drag_drop_condition();
//drag_drop_condition_value();
//condition_operator_type_selection();
//remove_from_dragged_element();
});

//get the new search criteria
$("#new_search_criteria_add").click(function(){
  $('#loading').show();
var new_search_criteria = $(".new_search_criteria").val();
$.ajax({
     url:'json.subinventory.php' ,
     data : { new_search_criteria : new_search_criteria},
     type: 'get'
     }).done(function(data){
      var div = $('#new_search_criteria', $(data)).html();
	  $("ul.search_form").append(div);       
        $('#loading').hide();
      }).fail(function(){
//     alert("org name loading failed");
     $('#loading').hide();
     });
});



}


 
);  
