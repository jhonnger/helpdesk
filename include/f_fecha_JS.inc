<?PHP
/*
    Nombre: f_fecha_JS.inc
    Autor: Julio Tuozzo
    Función: Funciones de manejo de fechas en JS
    Function: Functions of handling of dates in JS
    Ver: 2.0

*/
date_default_timezone_set('America/Lima');

echo
"    <script language='JavaScript'> \n";

## f_actualizo_fechas(): Coloca como fecha y fecha_ultimo_estado la fecha y hora actual.
// f_actualizo_fechas(): It places fecha and fecha_ultimo_estado the actual date and hour.

echo
"    function f_actualizo_fechas()
        { document.ticket.fecha.value=f_fecha();
          document.ticket.fecha_ultimo_estado.value=f_fecha();
        }\n";


## f_fecha(fecha), devuelve un string con la fecha y hora de "fecha", si "fecha"
## no esta inicializado devuelve la fecha de hoy.
// f_fecha(fecha), gives back string with the date and hour of “fecha”, if “fecha”
// does not initialized give back the date of today.

echo
"   function f_fecha(fecha)
        { if (typeof fecha=='undefined')
            {var fecha=new Date();
            }";
            
switch ($_SESSION['PHD_DATE_FORMAT'])
    {case "DMA":
          echo  "var fecha_u_e=f_cero(fecha.getDate())+'/'+f_cero((fecha.getMonth()+1))+'/'+fecha.getFullYear()+' '+f_cero(fecha.getHours())+':'+f_cero(fecha.getMinutes())+':'+f_cero(fecha.getSeconds());";
     break;

     case "MDA":
          echo  "var fecha_u_e=f_cero((fecha.getMonth()+1))+'/'+f_cero(fecha.getDate())+'/'+fecha.getFullYear()+' '+f_cero(fecha.getHours())+':'+f_cero(fecha.getMinutes())+':'+f_cero(fecha.getSeconds());";
     break;

     case "AMD":
          echo  "var fecha_u_e=fecha.getFullYear()+'/'+f_cero((fecha.getMonth()+1))+'/'+f_cero(fecha.getDate())+' '+f_cero(fecha.getHours())+':'+f_cero(fecha.getMinutes())+':'+f_cero(fecha.getSeconds());";
     break;

     default:
          echo  "var fecha_u_e=f_cero(fecha.getDate())+'/'+f_cero((fecha.getMonth()+1))+'/'+fecha.getFullYear()+' '+f_cero(fecha.getHours())+':'+f_cero(fecha.getMinutes())+':'+f_cero(fecha.getSeconds());";

    }

echo    "return fecha_u_e;
        }";


## f_cero: le coloca un cero a la izquierda si el número es de un dígito
// f_cero: it places a zero to him to the left if the number is of a digit

echo
"function f_cero(num) { return (num < 10) ? '0' + num : num; } \n

</script> \n";


?>

