<?PHP
    /*
    Nombre: lang.inc
    Autor: Julio Tuozzo
    Función: Plantilla de variables de idioma.
    Function: Group of language variables.
    Ver: 2.12
*/

    $_Vlang="2.12";


## Valores de variables internas
## IMPORTANTE: estos valores se guardan en la base de datos, NO SE DEBEN MODIFICAR
## una vez ingresados datos en la misma.

// Internal variables values.
// WARNING: These values are stored in the database, YOU MUST NOT MODIFY
// once you have data in it

    $_Contact="Contacto";
    $_Process="Proceso";
    $_State="Estado";
    $_Subtype="Subtipo";
    $_Type="Tipo";

### FIN DE VALORES QUE SE GUARDAN EN LA BASE DE DATOS
// END OF DATABASE VALUES

## Mensajes varios.
    $_And_press="y presione";
    $_Alert_assign_head="Aviso: se asign\u00F3 el ticket #%1% a (%2%) - %3%";
    $_Alert_tickets="tiene tickets en estado %1%";
    $_Are_data_loaded="Hay datos cargados y no han sido guardados, quiere salir de todas maneras?";
	$_Are_you_sure_cancel_file="Esta seguro de cancelar el archivo?";
    $_Are_you_sure_erase_log="Esta seguro de borrar el log?";
	$_Are_you_sure_load_file="Esta seguro de cargar el archivo?";
    $_By="por";
    $_Comment_added="Comentario agregado";
	$_Explain_load="Al presionar <em>Cargar</em> solo quendan activos los usuarios del archivo CSV, con los datos actualizados.";	
	$_File_loaded="Archivo cargado, %1% registros procesados";
    $_Input_the_code="Ingrese el c\u00F3digo que se muestra en la imagen superior";
    $_Mail_sent="Se ha enviado el correo con la contrase\u00F1a de ";
    $_No_mail_sent="Por alg\u00FAn motivo no se envi\u00F3 el correo con la contrase\u00F1a de";
    $_New_pswd_assigned="La contrase\u00F1a asignada es: ";
    $_Next="Siguiente";
    $_No="NO";
    $_None="[Ninguno]";
    $_Pswd_was_changed="Su contrase\u00F1a ha sido cambiada con \u00E9xito";
    $_Previous="Anterior";
    $_Pswd_expired="SU CONTRASE\u00F1A HA EXPIRADO, DEBE CAMBIARLA";
    $_Request_was_send="Se ha enviado la solicitud de soporte %1%, recuerde este n\u00FAmero para futuras referencias.";
    $_Subtype_of="Subtipo de";
    $_Ticket_was_stored="Se guardo; el ticket";
    $_User_doesnt_exists="El usuario no existe, complete los datos";
    $_Warning="¡¡ ATENCION !!";
    $_Was_modif="%1% fue modificado";
    $_Was_loaded="%1% fue ingresado";
    $_Yes="SI";
    $_Select_area="Seleccione \u00E1rea";

## Mensajes de error
    $_Are_opers_in="ERROR - Existen operadores activos en el sector";
    $_Are_users_in="ERROR - Existen usuarios activos en el \u00E1rea";
    $_Area_exists="El \u00E1rea ya existe";
    $_Area_input="El \u00E1rea no existe, ingrese el nombre";
    $_Attribute_exists_1="ERROR - EL ATRIBUTO";
    $_Attribute_exists_2="CON EL VALOR";
    $_Attribute_exists_3="YA EXISTE";
    $_Big_attach="El tama\u00F1o del archivo adjunto es mayor a %1%";
    $_Blank_name="El nombre no puede estar en blanco";
    $_Blank_value="ERROR - EL VALOR NO PUEDE ESTAR EN BLANCO";
    $_Cant_assign_private="No se puede asignar un operador de otro sector a un ticket privado";
    $_Cant_blank_value="No puede estar en blanco";
    $_Correct_err_to_cont="Corrija los errores para poder continuar.";
    $_Date_client_server_error="ERROR de fecha de servidor y equipo, la fecha del servidor es: ";
    $_Err_input_operator="ERROR - Ingrese operador";
    $_Err_input_passwd="ERROR - Ingrese su contrase\u00F1a";
    $_Err_level_access="Error de nivel de acceso";
    $_Err_max_row_1="ERROR - La consulta selecciona";
    $_Err_max_row_2="filas y el m\u00E1ximo permitido es de";
    $_Err_max_row_3="ampl\u00EDe el apellido y/o nombre";
    $_Err_parameters_file="Error en el archivo de par\u00E1metros, debe contener un registro y se han le\u00EDdo %1%";
    $_Error_captcha="ERROR - C\u00F3digo incorrecto";
    $_High_than_16m="No puede ser mayor a 16.000.000";
    $_Inactive_user="ERROR - Usuario inactivo";
    $_Invalid_character="CONTIENE UN CARACTER NO VALIDO - ERROR";
    $_Invalid_passwd="ERROR - Contrase\u00F1a inv\u00E1lida";
    $_No_database="Base no disponible por el momento";
    $_Lsd_lower_date="La fecha de \u00FAltimo estado es menor a la fecha";
    $_Mail_srv_err="El mensaje de error del servidor de correo fue";
    $_More_than_three_letters="Debe colocar al menos una palabra de m\u00E1s de tres letras";
    $_No_area="Falta ingresar el \u00E1rea";
   	$_No_assign="Asigne el ticket a un operador";
    $_No_attach="El archivo adjunto <i>%1%</i> no existe";
    $_No_contact="Falta ingresar el contacto";
    $_No_e_mail_usr="ERROR - El usuario no tiene un e-mail para enviarle la contrase\u00F1a";
    $_No_user="ERROR - Ingrese el usuario";
    $_No_last_name="Falta ingresar el apellido y nombre";
    $_No_incident="Falta ingresar el incidente";
    $_No_process="Falta ingresar el proceso";
    $_No_modif_attrib="No se puede modificar el %1% %2%, es un valor predeterminado";
    $_No_sector="Falta ingresar el sector";
    $_No_state="Falta ingresar el estado";
    $_No_user_found="No existen usuarios con";
    $_No_type="Falta ingresar el tipo";
  	$_No_upload_folder="No existe el subdirectorio \"upload\", cree ese subdirectorio en la ra\u00EDz de <strong>GRUPO CARITA FELIZ</strong>";
    $_No_valid_e_mail="La direcci\u00F3n de correo electr\u00F3nico no es v\u00E1lida";
    $_No_valid_format_lsd="Formato de fecha de \u00FAltimo estado inv\u00E1lido";
    $_No_valid_format_date_from="El formato de la fecha desde no es v\u00E1lido";
    $_No_valid_format_date_to="El formato de la fecha hasta no es v\u00E1lido";
    $_No_valid_format_lsd_from="El formato de la fecha \u00FAltimo estado desde no es v\u00E1lido";
    $_No_valid_format_lsd_to="El formato de la fecha \u00FAltimo estado hasta no es v\u00E1lido";
    $_Oper_exists="EL OPERADOR YA EXISTE";
    $_Oper_not_autorized="ERROR - El operador no esta autorizado para ingresar al sistema";
    $_Other_win_open="Hay otra ventana abierta con el ticket #%1%, no se puede guardar el ticket actual, cierre esta ventana y vuelva a abrirla.";
    $_Pswd_not_equal="ERROR - La nueva contrase\u00F1a y la reingresada no son iguales";
    $_Pswd_only_ln="ERROR - La nueva contrase\u00F1a debe tener solo letras y/o n\u00FAmeros";
    $_Pswd_repeat_d="ERROR - La nueva contrase\u00F1a tiene muchos d\u00EDgitos repetidos";
    $_Pswd_six_d="ERROR - La nueva contrase\u00F1a debe tener por lo menos seis d\u00EDgitos";
    $_Pswd_same_user="ERROR - La nueva contrase\u00F1a debe ser distinta al nombre de usuario";
    $_Pswd_same_act="ERROR - La contrase\u00F1a actual y la nueva son iguales";
    $_Pswd_used="ERROR - La nueva contrase\u00F1a ya se ha utilizado";
    $_Upper_than_cero="Debe ser un n\u00FAmero y mayor a cero.";
    $_UPR_error_found="ERRORES ENCONTRADOS:";
    $_User_exists="ERROR - El usuario ya existe";
    $_User_not_exists="ERROR - El usuario no existe";
    $_Sector_exists="El sector ya existe";
    $_Was_updated_1="ERROR - Este ticket ha sido actualizado por:";
    $_Was_updated_2="despu\u00E9s que se leyeron los datos del registro <br> Imposible realizar la actualizaci\u00F3n";


## Opciones de menú y links

    $_Advanced_query="Consulta avanzada";
    $_Areas="Areas";
    $_Attributes="Atributos";
    $_Check_last_version="Ver \u00FAltima versi\u00F3n";
	$_Consults="Consultas";
    $_E_mail_error_log="Log de errores de e-mail";
    $_Forgot_password="Olvid\u00E9 mi contrase\u00F1a";
    $_Help="Ayuda";
    $_Home="Inicio";
    $_Management_requests="Gesti\u00F3n de solicitudes";
    $_New_request="Nueva solicitud";
    $_New_ticket="Nuevo ticket";
	$_News="Novedades";
    $_Operators="Operadores";
    $_Load_users="Carga de usuarios y areas desde archivo";	
    $_Passwd_change="Cambio Contrase\u00F1a";
    $_Parameters="Par\u00E1metros";
    $_PHD_home="P\u00E1gina web de GRUPO CARITA FELIZ";
    $_Registry="Registrese";
    $_Sectors="Sectores";
    $_See_my_request="Ver mis solicitudes";
    $_Users_forum="Foro de usuarios";
    $_User_request_access="Acceso a solicitud de soporte de usuario";
    $_Users="Usuarios";
    $_User_guide="Manual de usuario";


## Títulos
    $_Administration="Administraci\u00F3n";
    $_Active="Activo";
    $_Area_admin="Administraci\u00F3n de \u00E1reas";
    $_Attribute_admin="Administraci\u00F3n de atributos del ticket";
    $_Body="Contenido";
    $_Change_active="Cambiar Activo SI/NO";
    $_Class_attribute="Clase de atributo";
    $_Comments="Comentarios";
    $_Default_values="Valores predeterminados del ticket";
    $_Enter_last_name="Ingrese Apellido y/o Nombre, completos o solo una parte";
    $_Error_message="Mensaje de error";
	$_File_content="Contenido del archivo";    
    $_Input_your_data="Ingrese sus datos";
   	$_Load_csv_file="Cargar archivo formato CSV";
    $_Load_user="Ingreso de Usuarios";
    $_Parameters_admin="Administraci\u00F3n de par\u00E1metros";
    $_Oper_pswd_change="Cambio de contrase\u00F1a de operador";
    $_Oper_admin="Administraci\u00F3n de operadores";
    $_Query_head="Filtro= ";
    $_Reason_request="Motivo de la solicitud";
    $_Sector_admin="Administraci\u00F3n de sectores";
    $_Support_request="Solicitud de soporte";
    $_Log_in="Ingreso al sistema";
    $_Receiver="Destinatario";
    $_Request_states="Estados de la solicitud de usuario";
    $_Sender="Remitente";
    $_Subject="Asunto";
    $_Tickets_assigned="Tickets asignados";
    $_Ticket_information="Datos del ticket";
    $_Total="Total";
    $_Total_request="Total de Solicitudes";
    $_Total_tkt="Total de Tickets";
    $_Tkt_follow_up="SEGUIMIENTO DEL TICKET";
    $_User_information="Datos del usuario";
    $_Users_admin="Administraci\u00F3n de usuarios";
    $_Value="Valor";
    $_Version="Versi\u00F3n 2.12 - Febrero 2012";
    
    

## Rótulos de campos
    $_Alert_assign="Avisar asignado";
    $_Alert_user_request="Avisar solicitud de usuario";
    $_Area="Area";
    $_Area_code="C\u00F3digo de \u00E1rea";
    $_Assigned_to="Asignado a";
    $_Attach_file="Adjuntar archivo";
    $_Attached_file="Archivo adjuntado";
    $_Date="Fecha";
    $_Detail="Detalle";
    $_Input_date="Fecha ingreso";
	$_Field_delimiter="Delimitador de campo";
    $_From="desde";
    $_To="hasta";
    $_Last_state_date="Fecha \u00FAltimo estado";
    $_Last_state_oper="Operador \u00FAltimo estado";
    $_Operator="Operador";
    $_User="Usuario";
    $_Password="Contrase\u00F1a";
    $_Last_and_first_name="Apellido y Nombre";
    $_Floor="Piso";
    $_Phone="Planta";
    $_Incident="Incidente";
    $_Input_by="Ingresado por";
    $_Comment="Comentario";
    $_Actual_pswd="Contrase\u00F1a actual";
    $_New_pswd="Nueva contrase\u00F1a";
    $_Retype_pswd="Reingrese nueva contrase\u00F1a";
    $_Elec_mail="Correo electr\u00F3nico";
    $_Access_level="Nivel de acceso";
    $_Administrator="Administrador";
    $_Name="Nombre";
    $_New_value="Nuevo valor";
    $_No_access="Sin acceso";
    $_Modified_field="Campo modificado";
    $_Previous_value="Valor anterior";
    $_Private="Privado";
    $_Priority="Prioridad";
    $_Request="Solicitud";
    $_Sector="Sector";
    $_Sector_code="C\u00F3digo de sector";
    $_Ticket="Ticket";
    $_Type_a_word="Ingrese una o m\u00E1s palabras separadas por espacio";
    $_User_visible="Visible para el usuario";
    
## Botones
    $_Add_comment="Agregar comentario";
    $_Cancel_file="Cancelar Archivo";
	$_Consult="Consultar";
    $_Download="Descargar";
    $_Enter="Entrar";
    $_Erase_log="Borrar log";
    $_Exit="Salir";
    $_Export="Exportar";
    $_Filter="Filtrar";
	$_Follow_up="Seguimiento";
    $_Gener_new_pswd="Generar nueva contrase\u00F1a";
    $_List="Listar";
   	$_Load="Cargar";
   	$_New="Nuevo";
    $_Open_ticket="Abrir ticket";
    $_Clean="Limpiar";
    $_Search="Buscar";
    $_Close="Cerrar";
    $_Cancel="Cancelar";
    $_Change="Cambiar";
    $_Save="Guardar";
    $_Search="Buscar";
    $_Show="Mostrar";
    $_Modif="Modificar";

## Mensajes de correo electrónico
    $_Access_at="Ingrese en";
    $_Alert_comment_subjet="Aviso: se agreg\u00F3; un comentario a su solicitud #%1%";
    $_Alert_ticket_comment_subjet="Aviso: el usuario (%1%) - %2% agreg\u00F3 un comentario al ticket #%3%";
    $_Alert_user_request_subjet="Aviso: se ingres\u00F3 la solicitud de soporte #%1%";
    $_Body_new_oper_1="Ha sido dado de alta en la plataforma Help Desk.";
    $_Body_new_pswd_1="Se ha modificado su contrase\u00F1a en la plataforma Help Desk.";
    $_Body_new_pswd_2="Su usuario es:";
    $_Body_new_pswd_3="y su contrase\u00F1a:";
    $_Body_new_pswd_4="El sistema le solicitar\u00E1 que cambie esta contrase\u00F1a una vez que haya ingresado.";
    $_Comment_added_by="Comentario agregado por %1%, el %2% a las %3%";
    $_Subject_new_oper="Alta en la plataforma Help Desk";
    $_Subject_new_pswd="Nueva contrase\u00F1a para su plataforma de Help Desk";
    $_Try_e_mail="Se intent\u00F3 enviar a la direcci\u00F3n de correo";
    $_Was_sended_to="Se envi\u00F3 a la direcci\u00F3n de correo";

## URLs
    $_User_guide_url="http://www.p-hd.com.ar/user_guide_2_12.php";
    $_Users_forum_url="http://www.p-hd.com.ar/foro.php";
    $_PHD_home_url="http://www.p-hd.com.ar";
    $_FAQ_url="http://www.p-hd.com.ar/faq_2_12.php";
    $_Registry_url="http://www.p-hd.com.ar/registro.php";
    $_Check_last_version_url="http://www.p-hd.com.ar/last_ver_2_12.php?ver=212";

## Otros textos

    $_DMA="dd/mm/aaaa";
    $_MDA="mm/dd/aaaa";
    $_AMD="aaaa/mm/dd";

    $_High="Alta";
    $_Medium="Media";
    $_Low="Baja";

    $_Explain_PEN="Primer estado de la solicitud cuando el usuario la ha ingresado, a\u00FAn no ha generado un ticket.";
    $_Explain_PAS="Estado de la solicitud cuando ha generado un ticket.";
    $_Explain_CAN="La solicitud no genera un ticket y se anula.";

	$_Explain_assign_ticket="Si se tilda este campo, los tickets se deben asignar obligatoriamente a un operador.";
    $_Explain_date_format="Formato de fecha";
    $_Explain_dias_psw="Cantidad de d\u00EDas en los que no se puede usar una contrase\u00F1a anterior como nueva contrase\u00F1a.";
    $_Explain_from_user_request=" Remitente del correo que se env\u00EDa a los operadores cuando se ingresa una solicitud de soporte.";
    $_Explain_from_user_psw="Remitente del correo que se env\u00EDa a los usuarios cuando generan su contrase\u00F1a.";
    $_Explain_max_attach="Tama\u00F1o m\u00E1ximo en bytes de un archivo adjunto al ticket, este valor no puede superar los 16000000.";
    $_Explain_max_dif_min="M\u00E1xima diferencia en minutos que puede haber entre el cliente que ejecuta <strong>Help Desk</strong> y el servidor de base de datos. Si no desea que <strong>Help Desk</strong> controle esta diferencia coloque este valor en 1440 o mayor.";
    $_Explain_max_lines_export="Cantidad m\u00E1xima de l\u00EDneas que se pueden exportar de la base.";
    $_Explain_max_lines_screen="Cantidad m\u00E1xima de l\u00EDneas que se muestran en una consulta por pantalla.";
    $_Explain_main_screen_state="Estado que tienen los tickets que se muestran asignados al operador en la pantalla inicial.";
    $_Explain_state_alert="Valor del estado que alertar\u00E1 al operador si ya hay un ticket ingresado para el mismo usuario.";
    $_Explain_validez_psw="Cantidad de d\u00EDas de validez de contrase\u00F1a para un operador.";
    $_Ticket_created="Su solicitud ha creado el ticket";

	$_Comma="Coma";
	$_Semicolon="Punto y coma";
	$_Tab="Tabulaci\u00F3n";

## Texto de formato de fecha

switch ($__SESSION['PHD_DATE_FORMAT'])
    {case "DMA":
         $_Date_text="dd/mm/aaaa";
         $_Date_format="d/m/Y";
     break;

     case "MDA":
         $_Date_text="mm/dd/aaaa";
         $_Date_format="m/d/Y";
     break;

     case "AMD":
         $_Date_text="aaaa/mm/dd";
         $_Date_format="Y/m/d";
     break;

     default:
         $_Date_text="dd/mm/aaaa";
         $_Date_format="d/m/Y";

    }

?>
