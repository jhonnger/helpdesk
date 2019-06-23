<?PHP
/*
    Nombre: atr_insert.inc
    Autor: Julio Tuozzo
    Función: Inserta el atributo en la tabla
    Function: Inserts the attribute in the table
    Ver: 2.00
*/

## Formateo los datos para insertarlos
// Formating the data before insert.

  $atributo=trim(strip_tags($_POST['atributo']));
  $valor=trim(strip_tags($_POST['valor']));
  $user=$_SESSION['PHD_OPERADOR'];

## Inicializo la variable para que quede seleccionada la clase de atributo en el<SELECT>
// Inicialicing the variables that make "selected" the <SELECT> attribute

switch ($atributo)
    {case $Contact:
     $opt_contact="selected";
     break;

     case $State:
     $opt_state="selected";
     break;

     case $Process:
     $opt_process="selected";
     break;

     case $Type:
     $opt_type="selected";
     break;

    }

## Valido datos antes de darlos de alta
// Valid the data before insert


   if (strlen($valor)<1)
    	{$mensaje=$Blank_value;
        }
   elseif (!preg_match('#^[-a-zA-Z0-9" "]+$#', $valor))
     	{$mensaje="$valor $Invalid_character";
        }
   else
   
        {## Verifico que no exista
         // Check that not exists
   
        $query="SELECT * FROM {$MyPHD}atributo WHERE atributo='$atributo' AND valor='$valor'";
        $result=mysql_query($query) or die (mysql_error());
   
        if (mysql_num_rows($result)>0)
                {$mensaje="$Attribute_exists_1 '$atributo' $Attribute_exists_2 '$valor' $Attribute_exists_3";
                }
        else

            ##  Lo doy de alta en la base
            {## Armo el query y lo ejecuto


             $query="INSERT INTO {$MyPHD}atributo VALUES
                (NULL,'$atributo',
					   '$valor',
					   'S',
					   '$user',
					   NOW(),
					   '$user',
					   NOW())";


            $insert=mysql_query($query) or die (mysql_error());
            // Blanqueo variables
            $mensaje=str_replace("%1%", "$atributo - $valor ",$Was_loaded );
            $valor='';

            }
        }

?>
