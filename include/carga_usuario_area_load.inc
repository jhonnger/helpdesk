<?PHP
/*
    Nombre: carga_usuario_area_load.inc
    Autor: Julio Tuozzo jtuozzo@p-hd.com.ar
    Función: Proceso que carga el archivo CSV en la tabla usuario_area_tmp
    Function: Load CSV file in the usuario_area_tmp 
    Ver: 2.12
*/

// Valido que haya algún archivo y que el tamaño no sea mayor al permitido
$archivo = $_FILES["archivo_csv"]["tmp_name"];
$tamanio_archivo = $_FILES["archivo_csv"]["size"];
$tipo_archivo = $_FILES["archivo_csv"]["type"];
$nombre_archivo = $_FILES["archivo_csv"]["name"];

$delimitador=$_POST['delimitador'];

if (strlen($nombre_archivo)<1) // valido que se haya ingresado un archivo
        {$mensaje=$mensaje."$UPR_error_found $Attach_file";
        }
elseif($tamanio_archivo>$_SESSION['PHD_MAX_ATTACH']) // verifico que el tamaño del archivo adjunto no sea mayor a $_SESSION[PHD_MAX_ATTACH].
	    { $Big_attach=str_replace("%1%",$text_max_attach,$Big_attach );
    	  $mensaje.="$Big_attach";
    	}
elseif ($tamanio_archivo<1) // valido que exista el archivo
        {$No_attach=str_replace("%1%"," $nombre_archivo ",$No_attach );
         $mensaje.="$UPR_error_found $No_attach";
        }
elseif(!is_readable("./upload/"))
		{$mensaje.="$UPR_error_found $No_upload_folder";
		}
else
	{// Guardo el archivo CSV en un temporal
	$ruta=substr($_SERVER['SCRIPT_FILENAME'],0,strrpos($_SERVER['SCRIPT_FILENAME'],"/"));
	$ruta=$ruta."/upload/";
	$archivo_upload=date("Y_m_d_H_i_s");
	$archivo_upload=$ruta.$archivo_upload.".csv";

	$fp = fopen($archivo,"rt");
	$fphd = fread($fp, $tamanio_archivo);
	fclose($fp);

	$fp = fopen($archivo_upload,"wt");
	$f700 = fwrite($fp, $fphd);
	fclose($fp);

	// Lo cargo en la tabla de archivos.
    $result=mysql_query("START TRANSACTION") or die (mysql_error());
    
	$query="LOAD DATA LOW_PRIORITY INFILE '$archivo_upload' 
	REPLACE
	INTO TABLE usuario_area_tmp
	FIELDS TERMINATED BY '$delimitador'
	OPTIONALLY ENCLOSED BY '\"'
	(usuario_id,
	 ape_y_nom,
	 e_mail,
	 piso,
	 planta,
	 area_id,
	 nombre)";
	 $insert=mysql_query($query) or die (mysql_error());
	 
	 // Elimino las claves vacías
	## Delete the empties keys

 	 $query="DELETE FROM usuario_area_tmp
	 WHERE LENGTH(usuario_id)=0 OR LENGTH(area_id)=0
	 OR LENGTH(ape_y_nom)=0 OR LENGTH(nombre)=0";

	 $result=mysql_query($query) or die (mysql_error());

	 $result=mysql_query("COMMIT") or die (mysql_error());

	}
	

?>
