<?PHP
/*
    Nombre: f_usuario_AJAX.php
    Autor: Julio Tuozzo
    Función: Rutina AJAX que recupera los datos del usuario y área
    Function: Retrieve user and area data AJAX routine.
    Ver: 2.12
*/
$Alert_tickets=str_replace("%1%",$_SESSION[PHD_STATE_ALERT],$Alert_tickets);
$ancho_mostrar=22+(strlen($Show)*8);
echo "
<script language='javascript'>
var READY_STATE_COMPLETE=4;
var peticion_http = null;

function inicializa_xhr()
        {if (window.XMLHttpRequest)
                {return new XMLHttpRequest();
                }
         else if (window.ActiveXObject)
                {return new ActiveXObject('Microsoft.XMLHTTP');
                }
        }
        
function crea_query_usuario()
       {var usuario = document.getElementById('usuario');
        return 'usuario=' + usuario.value + '&nocache=' + Math.random();
        }


function valida_usuario()
            {peticion_http = inicializa_xhr();
             if(peticion_http)
                   {peticion_http.onreadystatechange = Respuesta_usuario;
                    peticion_http.open('POST', 'http:usuario_select.php', true);
                    var query_string = crea_query_usuario();
                    peticion_http.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
                    peticion_http.send(query_string);
                   }
             }

function Respuesta_usuario()
            {if(peticion_http.readyState == READY_STATE_COMPLETE)
                   {if (peticion_http.status == 200  && peticion_http.responseText.length >1)
                        { var documento_xml = peticion_http.responseXML;
                          var root = documento_xml.getElementsByTagName('usuario')[0];

                          document.getElementById('ape_y_nom').value = root.getElementsByTagName('ape_y_nom')[0].firstChild?root.getElementsByTagName('ape_y_nom')[0].firstChild.nodeValue:'';
                          document.getElementById('area_id').value = root.getElementsByTagName('area_id')[0].firstChild?root.getElementsByTagName('area_id')[0].firstChild.nodeValue:'';
                          document.getElementById('piso').value = root.getElementsByTagName('piso')[0].firstChild?root.getElementsByTagName('piso')[0].firstChild.nodeValue:'';
                          document.getElementById('planta').value = root.getElementsByTagName('planta')[0].firstChild?root.getElementsByTagName('planta')[0].firstChild.nodeValue:'';
                          document.getElementById('e_mail').value = root.getElementsByTagName('e_mail')[0].firstChild?root.getElementsByTagName('e_mail')[0].firstChild.nodeValue:'';
                          document.getElementById('nombre_area').innerHTML = root.getElementsByTagName('nombre_area')[0].firstChild?root.getElementsByTagName('nombre_area')[0].firstChild.nodeValue:'';

                          document.getElementById('mensaje').innerHTML = '';
                          var alertas = root.getElementsByTagName('alertas')[0].firstChild.nodeValue;
                          if (alertas>0)
                                { var usuario = document.getElementById('usuario');
                                  var ape_y_nom = document.getElementById('ape_y_nom');
                                  var abro_ventana='consulta_result.php?pagina=1&q_registros='+alertas+'&orden=seq_ticket_id';
                                  document.getElementById('alert').innerHTML = '<b> $Warning</b> (' + usuario.value + ') -<em>' + ape_y_nom.value + '</em>- $Alert_tickets  <input id=\"alert_button\" class=\"boton_editar\" style=\"width: {$ancho_guardar}px;\" type=\"button\" value=\"$Show\" onclick=window.open(\"consulta.php?pagina=1&q_registros=0&orden=seq_ticket_id&menu=no\") />';

                                }
                          else
                                {document.getElementById('alert').innerHTML = '';
                                 document.getElementById('mensaje').innerHTML = '';
                                }
                          
                        }
                     else
                        {document.getElementById('mensaje').innerHTML = '$User_doesnt_exists';
                         document.getElementById('ape_y_nom').value = '';
                         document.getElementById('area_id').value = '';
                         document.getElementById('piso').value = '';
                         document.getElementById('planta').value = '';
                         document.getElementById('e_mail').value = '';
                         document.getElementById('nombre_area').innerHTML = '';
                         document.getElementById('alert').innerHTML = '';
                        }
                    }
            }
            
            
function crea_query_area()
       {var area_id = document.getElementById('area_id');
        return 'area_id=' + area_id.value + '&nocache=' + Math.random();
        }


function valida_area()
            {peticion_http = inicializa_xhr();
             if(peticion_http)
                   {peticion_http.onreadystatechange = Respuesta_area;
                    peticion_http.open('POST', 'http:area_select.php', true);
                    var query_string = crea_query_area();
                    peticion_http.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
                    peticion_http.send(query_string);
                   }
             }

function Respuesta_area()
            {if(peticion_http.readyState == READY_STATE_COMPLETE)
                   {if (peticion_http.status == 200)
                        { var documento_xml = peticion_http.responseXML;
                          var root = documento_xml.getElementsByTagName('area')[0];
                          document.getElementById('nombre_area').innerHTML = '<b>' + root.getElementsByTagName('nombre_area')[0].firstChild.nodeValue + '</b>';
                        }
                    }
            }

</script>
";
?>
