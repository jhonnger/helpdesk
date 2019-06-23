<?PHP
/*
    Nombre: ant_123_prox.inc
    Autor: Julio Tuozzo
    Function: Shows the navigation line of pages, <Prev | 1 2 3 ..... | Prox> in the consults.
    Version: 2.12
*/

## $pagina: Página que estoy mostrando 
## $q_registros: cantidad de registros de la consulta 
## $orden: orden de los registros.

echo "\n <div style='text-align:center'>";

if ($pagina>1)
    { $pag=$pagina-1;
      echo "<b><a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=$orden&sentido=$sentido&menu=$menu{$op_user}>
      <img src='./images/go-first.gif' alt='<<||' border='0' /></a> &nbsp;
      <a href=$_SERVER[PHP_SELF]?pagina=$pag&q_registros=$q_registros&orden=$orden&sentido=$sentido&menu=$menu{$op_user}>
      <img src='./images/go-previous.gif' alt='< Ant.|' border='0' /></b></a>";
    }

if(isset($q_registros) and $q_registros>0)
	{echo "<b>  &nbsp; Pag. &nbsp; </b>";
	}


if ($pagina>7)
    {$pag_desde=$pagina-6;
     echo "......";
    }
else
    {$pag_desde=1;
    }

for ($I=$_SESSION['PHD_MAX_LINES_SCREEN']*($pag_desde-1), $pag=$pag_desde ; $I<$q_registros; $I=$I+$_SESSION['PHD_MAX_LINES_SCREEN'], $pag++)
    { if ($pag==$pagina)
            {echo "<b><big> $pag </big>&nbsp;</b>";
            }
      else
            {echo "<a href=$_SERVER[PHP_SELF]?pagina=$pag&q_registros=$q_registros&orden=$orden&sentido=$sentido&menu=$menu{$op_user}> $pag </a> &nbsp; \n";
            }

      if ($pag-$pag_desde>14)
            {echo "......";
             break;
            }

    }


if ($pagina<($q_registros/$_SESSION['PHD_MAX_LINES_SCREEN']))
    {$pag=$pagina+1;
     $ultima=intval(($q_registros-1)/$_SESSION['PHD_MAX_LINES_SCREEN'])+1;
     echo "&nbsp;
           <a href=$_SERVER[PHP_SELF]?pagina=$pag&q_registros=$q_registros&orden=$orden&sentido=$sentido&menu=$menu{$op_user}><b>
           <img src='./images/go-next.gif' alt='|Sig.>' border='0' /></a> &nbsp;
           <a href=$_SERVER[PHP_SELF]?pagina=$ultima&q_registros=$q_registros&orden=$orden&sentido=$sentido&menu=$menu{$op_user}>
           <img src='./images/go-last.gif' alt='||>>' border='0' /></b></a>";
    }

echo "</div><br /> \n";

?>
