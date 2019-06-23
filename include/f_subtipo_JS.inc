<?PHP
/*
    Nombre: f_subtipo_JS.inc
    Autor: Julio Tuozzo
    Función: Función para insertar las opciones de subtipo en <SELECT>
    Function: Function to insert the options of subtype in <SELECT>
    Ver: 2.00

*/


#### f_sub_tipo(select del formulario): inserta las opciones de "subtipo" en función del tipo ingresado.

echo
"    <SCRIPT LANGUAGE='JavaScript'>


    function f_sub_tipo(elem)
        {
        for (var i = document.ticket.sub_tipo.options.length; i >= 0; i--)
            {document.ticket.sub_tipo.options[i] = null; \n";

   $query="SELECT b.atributo, b.valor
            FROM {$MyPHD}atributo a, {$MyPHD}atributo b
            WHERE a.valor=b.atributo and a.atributo='$Type' and b.activo='S' and a.activo='S'
            ORDER BY b.atributo, b.valor";

    $result=mysql_query($query) or die (mysql_error());

    $atributo_ant="";
    while ($row = mysql_fetch_array($result))
        {
        if($atributo_ant!=$row['atributo'])
            {$atributo_ant=$row['atributo'];
             echo
             "} if(elem.options[elem.selectedIndex].value=='$atributo_ant')\n {";
            }
        if ($row['valor']==$sub_tipo)
            {$selected='true';
            }
        else
            {$selected='false';
            }
        echo
        "document.ticket.sub_tipo.options[document.ticket.sub_tipo.options.length] = new Option('{$row['valor']}','{$row['valor']}',$selected,$selected);\n";

       }
echo
"   }
    }
</SCRIPT> \n";


?>

