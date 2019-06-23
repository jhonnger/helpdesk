<?PHP
    /*
    Nombre: config.inc.php
    Autor: Julio Tuozzo
    Funci�n: Plantilla de variables de conexi�n con la base de datos.
    Function: Group of variables of database conection.
    Ver: 2.12
*/
    $Host = 'localhost'; // Nombre del servidor de la base de datos MySQL.
                             // Name of the MySQL data base server.

    $Usuario = 'root'; // usuario con que PHD Help Desk se conectar� a la base de datos.
                           // user whereupon PHD Help Desk will connect to the MySQL data base.
                           
    $Contrasena = 'root'; // contrase�a del usuario.
                                  // User's password.

    $Base = 'helpdesk'; // nombre de la base de datos.
                    	         // data base name.

    $Include = './include/'; /* Ruta donde se encuentran los archivos que se llaman en require() / include ()
                                IMPORTANTE: Si quiere utilizar la ruta configurada en la variable "include_path" de php.ini
                                deje esta variable en blanco   
                              Path of the files called by  require() / include ()
                               WARNING: If you wish to use the path of the "include_path" variable, placed in php.ini file, leave
                               empty this variable*/
                              
                        
    $MyPHD = '';  // Prefijo de los nombres de las tablas en esta instalaci�n
                        // Tables name prefix in this installation.
                  
# Variables de conexi�n con el servidor de correo.
// E-mail server conection variables
    $Mail_host = "mail.clinicacaritafeliz.com";
    $Mail_usuario = "helpdesk@clinicacaritafeliz.com";
    $Mail_clave = "={EoaVg@A3Sy";
    $Mail_port = 465;

    # Variables de instalaci�n
    // Installation variables.
    $VPHD='2.12';
?>
