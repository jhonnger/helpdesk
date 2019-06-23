<?PHP
/*
    Nombre: set_tables.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Creación de tablas en la base de datos
    Ver: 2.12
*/

session_start();
require('../../config.inc.php');

if (!isset($_SESSION['TABLES']))
    {include('setup_head.inc');
     echo "<p class='danger'>LLAMADA INVALIDA</p>";
     exit();
    }

if(!mysql_connect($Host,$Usuario,$Contrasena) or !mysql_select_db($Base))
    {$mensaje="<h2 class='danger'>Error de conexi&oacute;n con la base de datos.</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }

if (!isset($_POST[b_tables]))
    {require('set_tables.inc');
     exit();
    }


## Verifico que no existan las tablas antes de crearlas

$tablas=" (area)(atributo)(ticket)(hist_pass)(operador)(parametros)(sector)(sigo_ticket)(solicitud)(usuario) (e_mail_error) (usuario_area_tmp)";

$query="SHOW TABLES";
$result=mysql_query($query) or die ("<p class='danger'> ERROR EN QUERY </p>");
while ($row = mysql_fetch_array($result))
    {if(strpos($tablas,"(".$row[0].")")>0)
        {if (!isset($mensaje))
            {$mensaje="<h2 class='danger'>ERROR - Las siguientes tablas ya existen en la base <i>$Base</i>:";
            }
         $mensaje.=" <br /> <i> - $row[0]</i>";

        }
    }

if (isset($mensaje))
    {$mensaje.="<br /> <br /><b>PHD Help Desk</b> intentar&aacute; crear tablas con estos nombres, no es posible continuar con el proceso de creaci&oacute;n de tablas hasta que las mismas no se encuentren m&aacute;s en la base: <i>$Base</i>. </h2>";
     require('set_tables.inc');
     exit();
    }


## Creo las tablas

if(!mysql_select_db($Base))
    {$mensaje="<h2 class='danger'>Error de conexi&oacute;n con la base: $Base</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS area (
        area_id varchar(15) NOT NULL,
        nombre varchar(50) NOT NULL,
        activo enum('S','N') NOT NULL default 'S',
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) NOT NULL,
        update_datetime datetime NOT NULL,
        PRIMARY KEY  (area_id))
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }

$query="CREATE TABLE IF NOT EXISTS atributo (
        seq_atrib_id mediumint(8) unsigned NOT NULL auto_increment,
        atributo varchar(20) NOT NULL,
        valor varchar(20) NOT NULL,
        activo char(1) NOT NULL,
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) NOT NULL,
        update_datetime datetime NOT NULL,
        PRIMARY KEY  (seq_atrib_id))
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS e_mail_error (
        insert_datetime datetime NOT NULL,
		from_name varchar(120) not null,	
		from_e_mail varchar(120) not null,
		to_name varchar(120) not null,	
		to_e_mail varchar(120) not null,
		subject varchar(120) not null,
		body text not null,
		error_message varchar(300) not null) 
		ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }



$query="CREATE TABLE IF NOT EXISTS hist_pass (
        operador_id varchar(15) NOT NULL,
        contrasenia varchar(255) NOT NULL,
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL)
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }

$query="CREATE TABLE IF NOT EXISTS operador (
        operador_id varchar(15) NOT NULL,
        ape_y_nom varchar(40) NOT NULL,
        sector_id varchar(15) NOT NULL,
        e_mail varchar(60) NOT NULL,
        contrasenia varchar(255) NOT NULL,
        privado enum('S','N') NOT NULL default 'S',
        nivel tinyint(4) NOT NULL default '0',
        expira_clave date NOT NULL,
        avisar_asignado enum('S','N') NOT NULL default 'N',
        avisar_solicitud enum('S','N') NOT NULL default 'N',
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) NOT NULL,
        update_datetime datetime NOT NULL,
        PRIMARY KEY  (operador_id))
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS parametros (
        validez_psw smallint(5) unsigned NOT NULL,
        dias_psw smallint(5) unsigned NOT NULL,
        max_lines_screen smallint(5) unsigned NOT NULL,
        max_lines_export mediumint(8) unsigned NOT NULL,
        max_dif_min smallint(5) unsigned NOT NULL,
        max_attach mediumint(8) unsigned NOT NULL,
        assign_ticket ENUM('S','N') NOT NULL DEFAULT 'N',
        from_user_request varchar(60) NOT NULL,
        from_user_psw varchar(60) NOT NULL,
        contact_default varchar(20) default NULL,
        process_default varchar(20) default NULL,
        state_default varchar(20) default NULL,
        state_alert varchar(20) default NULL,
        main_screen_state varchar(20) default NULL,
        date_format enum('DMA','MDA','AMD') NOT NULL default 'DMA',
        PEN varchar(20) NOT NULL,
        PAS varchar(20) NOT NULL,
        CAN varchar(20) NOT NULL,
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) NOT NULL,
        update_datetime datetime NOT NULL)
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Script table creation error</h2>
     MySQL error message: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE sector (
        sector_id varchar(15) NOT NULL,
        nombre varchar(50) NOT NULL,
        activo enum('S','N') NOT NULL default 'S',
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) NOT NULL,
        update_datetime datetime NOT NULL,
        PRIMARY KEY  (sector_id))
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS sigo_ticket (
  seq_sigo_ticket_id mediumint(8) unsigned NOT NULL auto_increment,
  seq_ticket_id mediumint(8) unsigned NOT NULL,
  fecha datetime NOT NULL,
  operador_id varchar(15) default NULL,
  usuario_id varchar(15) default NULL,
  campo_cambiado varchar(30) default NULL,
  valor_anterior varchar(60) default NULL,
  valor_actual varchar(60) default NULL,
  comentario text,
  visible enum('S','N') NOT NULL default 'N',
  adjunto mediumblob,
  tipo_adjunto varchar(128) default NULL,
  nombre_adjunto varchar(128) default NULL,
  insert_oper varchar(15) default NULL,
  insert_user varchar(15) default NULL,
  insert_datetime datetime NOT NULL,
  PRIMARY KEY  (seq_sigo_ticket_id),
  KEY (seq_ticket_id))
  ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }

$query="CREATE TABLE IF NOT EXISTS solicitud (
        seq_solicitud_id mediumint(8) unsigned NOT NULL auto_increment,
        fecha datetime NOT NULL,
        usuario_id varchar(15) NOT NULL,
        ape_y_nom varchar(50) NOT NULL,
        area varchar(15) NOT NULL,
        piso varchar(4) default NULL,
        e_mail varchar(60) default NULL,
        telefono varchar(30) default NULL,
        incidente text NOT NULL,
        estado enum('PEN','CAN','PAS') NOT NULL default 'PEN',
        seq_ticket_id mediumint(8) unsigned default NULL,
        insert_ip varchar(15) NOT NULL ,
        adjunto mediumblob,
        tipo_adjunto varchar(128) default NULL,
        nombre_adjunto varchar(128) default NULL,
        insert_user varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) default NULL,
        update_datetime datetime default NULL,
        PRIMARY KEY  (seq_solicitud_id))
  ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS ticket (
        seq_ticket_id mediumint(8) unsigned NOT NULL auto_increment,
        fecha datetime NOT NULL,
        privado enum('S','N') NOT NULL default 'S',
        operador_id varchar(15) NOT NULL,
        operador_sector_id varchar(15) NOT NULL,
        contacto varchar(20) NOT NULL,
        usuario_id varchar(15) NOT NULL,
        ape_y_nom varchar(50) NOT NULL,
        area_id varchar(15) NOT NULL,
        piso varchar(4) default NULL,
        telefono varchar(30) default NULL,
        e_mail varchar(60) default NULL,
        asignado_a varchar(15) default NULL,
        asignado_a_sector varchar(15) default NULL,
        prioridad tinyint(3) unsigned NOT NULL,
        incidente text NOT NULL,
        proceso varchar(20) NOT NULL,
        tipo varchar(20) NOT NULL,
        sub_tipo varchar(20) default NULL,
        estado varchar(20) NOT NULL,
        fecha_ultimo_estado datetime NOT NULL,
        operador_ultimo_estado varchar(15) default NULL,
        adjunto mediumblob,
        tipo_adjunto varchar(128) default NULL,
        nombre_adjunto varchar(128) default NULL,
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) NOT NULL,
        update_datetime datetime NOT NULL,
        PRIMARY KEY  (seq_ticket_id),
        KEY (estado),
        KEY (proceso),
        KEY (fecha))
  ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS usuario (
        usuario_id varchar(15) NOT NULL,
        ape_y_nom varchar(50) NOT NULL,
        area_id varchar(15) NOT NULL,
        e_mail varchar(60) default NULL,
        piso varchar(4) default NULL,
        telefono varchar(30) default NULL,
        activo enum('S','N') NOT NULL default 'S',
        contrasenia varchar(255) default NULL,
        cambia_clave enum('S','N') NOT NULL default 'S',
        insert_oper varchar(15) NOT NULL,
        insert_datetime datetime NOT NULL,
        update_oper varchar(15) default NULL,
        update_user varchar(15) default NULL,
        update_datetime datetime NOT NULL,
        PRIMARY KEY  (usuario_id))
        ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }


$query="CREATE TABLE IF NOT EXISTS usuario_area_tmp (
        usuario_id varchar(15) not null,
		ape_y_nom varchar(50) not null,
		e_mail varchar(60),
		piso varchar(4),
		telefono varchar(30),
		area_id varchar(15) not null,
		nombre varchar(50) not null,
		PRIMARY KEY (usuario_id)) 
		ENGINE=InnoDB";

if(!mysql_query($query))
    {$mensaje="<h2 class='danger'>Error en la ejecuci&oacute;n del script de creaci&oacute;n de tablas</h2>
     Mensaje de error de MySQL: ".mysql_error();
     require('set_tables.inc');
     exit();
    }
    
session_destroy();
header("Location: index.php");
?>
