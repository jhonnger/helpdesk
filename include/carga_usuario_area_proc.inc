<?PHP
/*
    Nombre: carga_usuario_area_proc.inc
    Autor: Julio Tuozzo jtuozzo@p-hd.com.ar
    Función: Actualiza las tablas usuario y area con el contenido de usuario_area_tmp
    Function: Update the usuario and area tables with the usuario_area_tmp content
    Ver: 2.12
*/

$result=mysql_query("START TRANSACTION") or die (mysql_error());
// Primero dejo inactivos todos los usuarios y áreas
## At first deactive all the users and areas.

$query="UPDATE usuario SET activo='N'";
$result=mysql_query($query) or die (mysql_error());
 
$query="UPDATE area SET activo='N'";
$result=mysql_query($query) or die (mysql_error());

// Recorro la tabla usuario_area_tmp y proceso los registros.

$query="SELECT * from usuario_area_tmp";
$result=mysql_query($query) or die (mysql_error());
$q_filas=mysql_num_rows($result);

while ($row = mysql_fetch_array($result))
	{$query="SELECT count(*) as cuantos
			 FROM usuario 
			 WHERE usuario_id='{$row['usuario_id']}'";
			 
	 $res=mysql_query($query) or die (mysql_error());
	 $row0 = mysql_fetch_array($res);
	 
	 if($row0['cuantos']==0)
	 		{$query="INSERT INTO usuario VALUES
			 		('{$row['usuario_id']}',
			 		 '{$row['ape_y_nom']}',
			 		 '{$row['area_id']}',
			 		 '{$row['e_mail']}',
			 		 '{$row['piso']}',
			 		 '{$row['planta']}',
			 		 'S',
			 		 null,
			 		 'S',
			 		 '{$_SESSION['PHD_OPERADOR']}',
			 		 NOW(),
			 		 '{$_SESSION['PHD_OPERADOR']}',
			 		 null,
			 		 NOW())";	
			}
	 else
			{$query="UPDATE usuario SET
			 		 ape_y_nom='{$row['ape_y_nom']}',
			 		 area_id='{$row['area_id']}',
			 		 e_mail='{$row['e_mail']}',
			 		 piso='{$row['piso']}',
			 		 planta='{$row['planta']}',
			 		 activo='S',
			 		 update_oper='{$_SESSION['PHD_OPERADOR']}',
			 		 update_datetime=NOW(),
			 		 update_user=null
					 WHERE usuario_id='{$row['usuario_id']}'";
			
			}		 
 	 $res=mysql_query($query) or die (mysql_error());
	}


$query="SELECT distinct area_id, nombre 
		FROM usuario_area_tmp";

$result=mysql_query($query) or die (mysql_error());

while ($row = mysql_fetch_array($result))
	{$query="SELECT count(*) as cuantos
			 FROM area 
			 WHERE area_id='{$row['area_id']}'";
			 
	 $res=mysql_query($query) or die (mysql_error());
	 $row0 = mysql_fetch_array($res);
	 
	 if($row0['cuantos']==0)
	 		{$query="INSERT INTO area VALUES
			 		('{$row['area_id']}',
			 		 '{$row['nombre']}',
			 		 'S',
			 		 '{$_SESSION['PHD_OPERADOR']}',
			 		 NOW(),
			 		 '{$_SESSION['PHD_OPERADOR']}',
			 		 NOW())";
			}
	 else
			{$query="UPDATE area SET
			 		 nombre='{$row['nombre']}',
			 		 activo='S',
			 		 update_oper='{$_SESSION['PHD_OPERADOR']}',
			 		 update_datetime=NOW()
				     WHERE area_id='{$row['area_id']}'";
			
			}		 
 	 $res=mysql_query($query) or die (mysql_error());
	}

$query="DELETE FROM usuario_area_tmp";

$result=mysql_query($query) or die (mysql_error());

$result=mysql_query("COMMIT") or die (mysql_error());
unset($_GET);
$proceso_ok=str_replace("%1%",$q_filas,$File_loaded);
$proceso_ok="<h3 class='error'>$proceso_ok.</h3>";

?>
