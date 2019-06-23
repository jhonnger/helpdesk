<?PHP
    /*
    Nombre: lang.inc
    Autor: Julio Tuozzo
    Función: Plantilla de variables de idioma.
    Function: Group of language variables.
    Ver: 2.12
*/

   $Vlang="2.12";

// Values of internal variables

// IMPORTANT: these values keep in the database, ARE NOT DUE TO MODIFY
// once entered data in the database.

    $Contact="Contact";
    $Process="Process";
    $State="State";
    $Subtype="Subtype";
    $Type="Type";


## Mensajes varios.
    $And_press="and press";
    $Alert_assign_head="Alert: the ticket: #%1% was assigned to (%2%) - %3%";
    $Alert_tickets="has tickets in %1% state";
    $Are_data_loaded="There are loaded data and they have not been save, wants to go out any way? ";
	$Are_you_sure_cancel_file="Are you sure cancel file?";
   	$Are_you_sure_erase_log="Are you sure erase log?";
	$Are_you_sure_load_file="Are you sure load file?";
    $Area_input="The area does not exist, enters the name";
    $Area_exists="The area already exists";
    $By="by";
    $Comment_added="Comment added";
    $Explain_from_user_request="Sender of the e-mail that send to an operator when a support request is loaded.";
	$File_content="File content";
	$File_loaded="File loaded, %1% proccesed rows";
    $Input_the_code="Input the code showed in the image below";
    $Mail_sent="Have been sent the e-mail with the password of ";
    $Next="Next";
    $New_pswd_assigned="The assigned password is: ";
    $No="NO";
    $No_mail_sent="By some reason the mail with the password was not sent of";
    $None="[None]";
    $Pswd_was_changed="Your password was changed";
    $Previous="Previous";
    $Pswd_expired="YOUR PASSWORD HAS EXPIRED, MUST CHANGE IT";
    $Request_was_send="Has been sent the support request %1%, remember this number for future references.";
    $Select_area="Select area";
    $Subtype_of="Subtype of";
    $Ticket_created="Your request has been created the ticket";
    $Ticket_was_stored="Stored ticket";
    $User_doesnt_exists="The user does not exist, complete the data";
    $Warning="¡¡ WARNING !!";
    $Was_loaded="%1% was loaded";
    $Was_modif="%1% was modifyed";
    $Was_sended_to="Was sended to email address";
    $Yes="YES";


## Error messages.
    $Are_opers_in="ERROR - There are active operators in the sector";
    $Are_users_in="ERROR - There are active users in the area";
    $Attribute_exists_1="ERROR - THE ATTRIBUTE";
    $Attribute_exists_2="WITH THE VALUE";
    $Attribute_exists_3="EXISTS";
    $Big_attach="The size of the attached file is bigger than %1%";
    $Blank_name="The name can´t be blank";
    $Blank_value="ERROR - THE VALUE CAN'T BE BLANK";
    $Cant_assign_private="Can´t assign an other sector operator to a private ticket";
    $Cant_blank_value="Can't be a blank value";
    $Correct_err_to_cont="Correct errors to continue.";
    $Date_client_server_error="ERROR of date of server and local PC, the date of the server is:  ";
    $Err_input_operator="ERROR - Enter operator";
    $Err_input_passwd="ERROR - Enter your password";
    $Err_level_access="Error of access level";
    $Err_max_row_1="ERROR - The query select";
    $Err_max_row_2="rows and the highest allowed is";
    $Err_max_row_3="extend the last name and/or name ";
    $Err_parameters_file="Parameters file (parametros) error, must had one record and was reading %1%";
    $Error_captcha="ERROR - Wrong code";
    $High_than_16m="Can't be upper than 16.000.000";
    $Inactive_user="ERROR - Inactive user";
    $Invalid_character="HAS AN INVALID CHARACTER - ERROR";
    $Invalid_passwd="ERROR - Invalid Password";
    $No_database="No database avaiable";
    $Lsd_lower_date="The date of last state is smaller than the date";
    $Mail_srv_err="The email server message was";
    $More_than_three_letters="You must place one word of more at least than three letters ";
	$No_assign="Assign the ticket to operator";
    $No_attach="The attached file <i>%1%</i> does not exists";
    $No_user="ERROR - input user";
    $No_last_name="There aren't last name and name";
    $No_area="There aren't area";
    $No_contact="Lack to enter the contact";
    $No_e_mail_usr="ERROR - The user has not an e-mail to send the password";
	$No_upload_folder="Do not exists the folder \"upload\", create it in the root of <strong>PHD Help Desk</strong>";
    $No_incident="There aren't incident";
    $No_modif_attrib="Can't modify the %2% %1%, it's a default value";
    $No_process="There isn't process";
    $No_sector="There is not sector";
    $No_state="There aren't state";
    $No_type="There isn't type";
    $No_user_found="Do not exist user with";
    $No_valid_e_mail="Invalid e-mail address";
    $No_valid_format_lsd="Invalid format of last state date";
    $No_valid_format_date_from="Invalid format of date from";
    $No_valid_format_date_to="Invalid format of date to";
    $No_valid_format_lsd_from="Invalid format of last state date from";
    $No_valid_format_lsd_to="Invalid format of last state date to";
    $Oper_exists="THE OPERATOR EXISTS";
    $Oper_not_autorized="ERROR - The operator are not authorized to enter in the system" ;
    $Other_win_open="There is other windows open with the ticket #%1%, can not save this ticket, close this windows and open again.";
    $Pswd_not_equal="ERROR - The new password and the retype one are not equal";
    $Pswd_only_ln="ERROR - The new password must have letters and/or numbers ";
    $Pswd_repeat_d="ERROR - The new password has many repeated digits";
    $Pswd_six_d="ERROR - The new password must have six digits at least";
    $Pswd_same_user="ERROR - The new password must be different to the operator name";
    $Pswd_same_act="ERROR - The actual password and the new password are the same";
    $Pswd_used="ERROR - The new password was used";
    $Sector_exists="THE SECTOR EXISTS";
    $Try_e_mail="Fail when attemp to send the email to address";
    $Upper_than_cero="Must be a number upper than zero.";
    $UPR_error_found="ERRORS FOUND:";
    $User_exists="ERROR - The user exists";
    $User_not_exists="ERROR - The user does not exists";
    $Was_updated_1="ERROR - This ticket was update for:";
    $Was_updated_2="after read the registry data<br> Is not possible up date it";


## Menu options and others links
    $Advanced_query="Advanced query";
    $Areas="Areas";
    $Attributes="Attributes";
    $Check_last_version="Check last version";
	$Consults="Consults";
   	$E_mail_error_log="E-mail error log";			
	$Follow_up="Follow up";
    $Forgot_password="Forgot my password";
    $Help="Help";
    $Home="Home";
    $Management_requests="Requests management";
    $New_request="New request";
    $New_ticket="New ticket";
	$News="News";
    $Operators="Operators";
    $Passwd_change="Password change";
    $Parameters="Parameters";
    $PHD_home="PHD Help Desk home page";
    $Registry="Register";
    $See_my_request="See my requests";
    $User_guide="User guide";
    $Users_forum="Users forum";
    $User_request_access="Web user request access";
    $Users="Users";

## Titles
    $Active="Active";
    $Administration="Administration";
    $Alert_user_request="Alert user request";
    $Area_admin="Areas administration";
    $Attribute_admin="Ticket attributes administration";
   	$Body="Body";
    $Change_active="Change active YES/NO";
    $Class_attribute="Attribute class";
    $Default_values="Default ticket values";
    $Input_your_data="Input your data";
    $User_information="User information";
    $Ticket_information="Ticket information";
    $Enter_last_name="Input last name and/or name, complette or a part of it";
    $Load_user="Users load";
   	$Load_users="Load users and areas from a file";	
	$Load_csv_file="Load CSV file";
    $Log_in="System access";
    $Oper_pswd_change="Operator password change";
    $Oper_admin="Operator administration";
    $Parameters_admin="Parameters administration";
    $Query_head="Filter= ";
    $Request_states="User request states";
    $Sector_admin="Sectors administration";
    $Support_request="Support request";
    $Tickets_assigned="Tickets assigned";
    $Total="Total";
    $Total_request="Total of Requests";
    $Total_tkt="Total tickets";
    $Tkt_follow_up="TICKET FOLLOW UP";
    $Users_admin="Users administration";
    $Value="Value";
    $Version="Version 2.12 - February 2012";


## Field labels

    $Access_level="Access level";
    $Administrator="Administrator";
    $Alert_assign="Assign alert";
    $Area_code="Area code";
    $Assigned_to="Assigned to";
    $Attach_file="Attach file";
    $Attached_file="Attached file";
	$Comma="Comma";
    $Comments="Comments";
    $Date="Date";
    $Detail="Detail";
   	$Error_message="Error message";
	$Field_delimiter="Field delimiter";
    $Input_by="Input by";
    $Input_date="Input date";
    $From="from";
    $To="to";
    $Last_state_date="Last state date";
    $Last_state_oper="Last state operator";
   	$New="New";
    $Operator="Operator";
    $User="User";
    $Area="Area";
    $Name="Name";
    $Password="Password";
    $Last_and_first_name="Last name and name";
    $Floor="Floor";
    $Phone="Phone";
    $Priority="Priority";
    $Private="Private";
    $Incident="Incident";
    $Comment="Comment";
    $Actual_pswd="Actual password";
    $New_pswd="New password";
    $Reason_request="Request reason";
    $Retype_pswd="Retype new password";
    $Ticket="Ticket";
    $Elec_mail="E-mail";
    $No_access="No access";
    $Modified_field="Modified field";
    $Request="Request";
    $Previous_value="Previous value";
    $New_value="New value";
  	$Receiver="Receiver";
  	$Sender="Sender";
    $Semicolon="Semicolon";
   	$Subject="Subject";
    $Sector="Sector";
    $Sectors="Sectors";
    $Sector_code="Sector code";
	$Tab="Tabs";
    $Type_a_word="Type one or more words separated by a blank";
    $User_visible="Visible for the user";


## Buttons

    $Add_comment="Add comment";
    $Cancel="Cancel";
	$Cancel_file="Cancel File";
    $Change="Change";
    $Clean="Clean";
    $Close="Close";
    $Consult="Consult";
    $Enter="Enter";
 	$Erase_log="Erase log";			
    $Exit="Exit";
    $Export="Export";
    $Gener_new_pswd="Generate new password";
    $List="List";
	$Load="Load";
    $Modif="Modify";
    $Open_ticket="Open ticket";
    $Save="Save";
    $Show="Show";
    $Search="Search";
    $Filter="Filter";
    $Download="Download";

## E-mail menssages

    $Access_at="Go to";
    $Alert_comment_subjet="Alert: a comment was added on your request #%1%";
    $Alert_ticket_comment_subjet="Alert: The user (%1%) - %2% was added a comment on the ticket #%3%";
    $Alert_user_request_subjet="Alert: The support request #%1% was loaded ";
    $Body_new_oper_1="You has been registered in PHD Help Desk.";
    $Body_new_pswd_1="Your password in PHD Help Desk has been modified. ";
    $Body_new_pswd_2="Your user is:";
    $Body_new_pswd_3="and your password:";
    $Body_new_pswd_4="You must change this password once you have entered.";
    $Comment_added_by="Comment added by %1%, on %2% at %3%";
    $Subject_new_oper="Registry in PHD Help Desk";
    $Subject_new_pswd="New password in PHD Help Desk";

## URLs

    $User_guide_url="http://www.p-hd.com.ar/eng/user_guide_2_12.php";
    $Users_forum_url="http://www.p-hd.com.ar/eng/foro.php";
    $PHD_home_url="http://www.p-hd.com.ar/eng/";
    $FAQ_url="http://www.p-hd.com.ar/eng/faq_2_12.php";
    $Check_last_version_url="http://www.p-hd.com.ar/eng/last_ver_2_12.php?ver=212";
    $Registry_url="http://www.p-hd.com.ar/eng/registro.php";

## Other texts

    $DMA="dd/mm/yyyy";
    $MDA="mm/dd/yyyy";
    $AMD="yyyy/mm/dd";


    $High="High";
    $Medium="Medium";
    $Low="Low";

	$Explain_assign_ticket="If you check this field, the tickets must be assigned to an operator.";
    $Explain_date_format="Date format";
    $Explain_dias_psw="Amount of days in which a previous password like new password cannot be used.";
    $Explain_from_user_psw="E-mail from address that will send to the users when they change the password.";
	$Explain_load="When press <em>Load</em> only stay active the users in the CSV file with the data updated.";	
    $Explain_main_screen_state="Operator assigned tickets state that show in the main screen.";
    $Explain_max_attach="Maximum size in bytes of an attached file to the ticket, this value do not pass 16000000.";
    $Explain_max_dif_min="Max difference in minutes that can have between the client who executes <strong>PHD Help Desk</strong> and the database server. If it does not wish that <strong>PHD Help Desk</strong> controls this difference place this value in 1440 or high.";
    $Explain_max_lines_export="Maximum lines that can be exported of the data base.";
    $Explain_max_lines_screen="Maximum lines that are in a query by screen.";
    $Explain_state_alert="State value that alerts to an operator when other ticket for the same user is loaded.";
    $Explain_validez_psw="Amount of days of validity of password for an operator.";

    $Explain_PEN="First user request state, do not exists ticket yet.";
    $Explain_PAS="User request state when the ticket was created.";
    $Explain_CAN="The user request do not creates a ticket and is canceled.";



## Date Format texts

switch ($_SESSION['PHD_DATE_FORMAT'])
    {case "DMA":
         $Date_text="dd/mm/yyyy";
         $Date_format="d/m/Y";
     break;
     case "MDA":
         $Date_text="mm/dd/yyyy";
         $Date_format="m/d/Y";
     break;
     case "AMD":
         $Date_text="yyyy/mm/dd";
         $Date_format="Y/m/d";
     break;

     default:
         $Date_text="dd/mm/yyyy";
         $Date_format="d/m/Y";

    }
?>
