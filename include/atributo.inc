<?PHP
/*
    Nombre: atributo.inc
    Autor: Julio Tuozzo
    Función: Vista de administración de atributos de los casos.
    Function: Tickets attributes administration view.
    Ver: 2.12

*/
$opcion=$Attribute_admin;
include('head_frame.inc');

## Formulario de ingreso de datos del atributo.
// Attribute data input form.

echo "<body>";
require('menu.inc');
echo "<div id='contenido'>
    <div class='error'> $mensaje </div>
    <form method='post' action=$_SERVER[PHP_SELF]>

     $Class_attribute:
          <SELECT name='atributo'>
              <OPTION $opt_contact> $Contact </OPTION>
              <OPTION $opt_state> $State </OPTION>
              <OPTION $opt_process> $Process </OPTION>
              <OPTION $opt_type> $Type </OPTION>";

        $query="SELECT valor
            FROM {$MyPHD}atributo
            WHERE atributo='$Type' AND activo='S'
            ORDER BY valor";
    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
       { if ($atributo==$row[valor])
            {$opt_selected="selected";
            }
         else
            {$opt_selected="";
            }

         echo "<OPTION value='$row[valor]' $opt_selected> $Subtype_of $row[valor] </OPTION> \n";
	   }

$ancho_guardar=22+(strlen($Save)*8);
$ancho_salir=22+(strlen($Home)*8);

echo "
          </SELECT>
    &nbsp; &nbsp;
    $Value: <input type='text' name='valor' size='20' maxlength='20' value='$valor' >  &nbsp; &nbsp;

           <TABLE border='0' cellspacing='1' cellpadding='5' width='100%'>
             <tr>
              <td align='right'>
               <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$Save' name='guardar'>
              </td>
              <td align='right' >
               <input class='boton_salir' style='width: {$ancho_salir}px;' type='submit' value='$Home' name='salir'>
              </td>
             </tr>
           </TABLE>
   </FORM>";

## Muestro los datos de los atributos
// Show the attribute data

echo "
 <iframe src='atributo_list.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' onLoad='this.style.height=document.body.clientHeight-this.offsetTop-75;' />


  </body>
</html>";


?>

