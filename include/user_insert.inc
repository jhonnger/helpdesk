<?PHP
/*
    Nombre: user_insert.inc
    Autor: Julio Tuozzo
    Función: Valida los datos del usuario y lo da de alta en la base
    Function: User data validation and input in the database.
    Ver: 2.05
*/

## Preparo los datos para insertarlos
// Prepare the data before insert

if (get_magic_quotes_gpc())
     { foreach($_POST as $clave => $valor)
         {$_POST[$clave]=stripslashes($_POST[$clave]);
         }
     }
foreach($_POST as $clave => $valor)
      {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
      }


  $usuario_id=$_POST['usuario_id'];
  $ape_y_nom=$_POST['ape_y_nom'];
  $e_mail=$_POST['e_mail'];
  $piso=$_POST['piso'];
  $planta=$_POST['planta'];
  $user=$_SESSION['PHD_OPERADOR'];
  $area_id=$_POST['area_id'];

    if ($_POST[activo]=="1")
        {$activo="S";
         $active_check="checked";
        }
    else
        {$activo="N";
         $active_check="";
        }


## Valido datos antes de darlos de alta
// Valid data before insert in the database.

    if (strlen($usuario_id)<1)
    	{$mensaje=$No_user;
        }
    elseif (!preg_match('#^[-_a-zA-Z0-9]+$#', $usuario_id))
     	{$mensaje="$usuario_id $Invalid_character";
        }
    elseif (strlen($ape_y_nom)<1)
   	    {$mensaje=$No_last_name;
	    }
    elseif (strlen($e_mail)>0 and !preg_match('#^.+@.+\\..+$#',$e_mail))
   	    {$mensaje=$No_valid_e_mail;
	    }

    elseif (strlen($area_id)<1)
   	    {$mensaje=$No_area;
	    }

        else
        {
	       $query="SELECT * FROM {$MyPHD}usuario WHERE usuario_id='$usuario_id'";
	       $result=mysql_query($query) or die (mysql_error());
	       $q_filas=Mysql_num_rows($result);
	
           if ($q_filas>0)
	           {$mensaje=$User_exists;
	           }
	       else

##  Lo doy de alta en la base
// Input in the database
	           {$ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
                ## Armo el insert y lo ejecuto
                // Make the insert and execute it


                       $query="INSERT INTO {$MyPHD}usuario VALUES ('$usuario_id',
					   '$ape_y_nom',
					   '$area_id',
					   '$e_mail',
					   '$piso',
					   '$planta',
					   '$activo',
					   null,
					   'S',
					   '$user',
					   NOW(),
					   '$user',
					   null,
					   NOW())";

               $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
    	       $insert=mysql_query($query) or die (mysql_error());

               // Blanqueo variables
               $mensaje=str_replace("%1%", "$usuario_id - $ape_y_nom ",$Was_loaded );
               $piso=$planta=$e_mail=$ape_y_nom=$usuario_id='';


      	     }
          }



?>
