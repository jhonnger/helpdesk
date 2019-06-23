<?PHP
/*
    Nombre: opr_mod.inc
    Autor: Julio Tuozzo
    Función: Valida los datos del operador y lo modifica en la base.
    Function: Verify the data of the operator data and update the database
    Ver: 2.00
*/

## Preparo los datos para modificar
// Prepare the data to modify
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

$operador=$_POST['operador'];
$ape_y_nom=$_POST['ape_y_nom'];
$e_mail=$_POST['e_mail'];
$sector_id=$_POST['sector_id'];
$user=$_SESSION['PHD_OPERADOR'];

   switch ($_POST['nivel'])
            {case $Administrator:
                $_20='selected';
                $nivel=20;
                break;
             case $Operator:
                $_10='selected';
                $nivel=10;
                break;
             default:
                $_0='selected';
                $nivel=0;
            }

    if ($_POST[privado]=="1")
        {$privado="S";
         $private_check="checked";
        }
    else
        {$privado="N";
         $private_check="";
        }

    if ($_POST[avisar_asignado]=="1")
        {$avisar_asignado="S";
         $avisar_asignado_check="checked";
        }
    else
        {$avisar_asignado="N";
         $avisar_asignado_check="";
        }

     if ($_POST[avisar_solicitud]=="1")
        {$avisar_solicitud="S";
         $avisar_solicitud_check="checked";
        }
    else
        {$avisar_solicitud="N";
         $avisar_solicitud_check="";
        }


## Valido datos antes de darlos de alta
// Valid the data before modifing

    if (strlen($ape_y_nom)<1)
   	    {$mensaje=$No_last_name;
	    }

    elseif (!preg_match('#^.+@.+\\..+$#',$e_mail))
   	    {$mensaje=$No_valid_e_mail;
	    }

    elseif (strlen($sector_id)<1)
   	    {$mensaje=$No_sector;
	    }

        else

##  Modifico los datos en la base
        {$ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
	     $query="UPDATE {$MyPHD}operador
                 SET
                 ape_y_nom='$ape_y_nom',
                 sector_id='$sector_id',
                 e_mail='$e_mail',
                 privado='$privado',
				 nivel='$nivel',
				 avisar_asignado='$avisar_asignado',
				 avisar_solicitud='$avisar_solicitud',
				 update_oper='$user',
			     update_datetime=NOW()
			     WHERE
			     operador_id='$operador'";

                 $update=mysql_query($query) or die (mysql_error());

          }

// Blanqueo variables
$_20=$_10=$_0=$e_mail=$ape_y_nom=$operador=$avisar_solicitud_check=$avisar_asignado_check=$sector_id='';

?>
