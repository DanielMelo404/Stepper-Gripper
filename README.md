# Stepper-Gripper
Three fingers gripper with stepper motor
![image](https://github.com/DanielMelo404/Stepper-Gripper/assets/37639887/8654a8c3-b7c9-4a19-9e8a-1e8d556fc3fe)



\section{Estado del arte - BCI:}
Una interfaz cerebro-computador es el conjunto de hardware y software que permite controlar dispositivos externos con señales cerebrales \cite{RAMADAN201726}.
El origen de este campo de investigación sucede en 1924 con Berger, el cual hace el primer grabado de señales por electro encefalografia (EEG), e identifica el patrón oscilatorio, con las ondas alpha (8-13Hz).


\section{Objetivos actuales del campo:}
\begin{itemize}
    \item Mejorar la calidad de vida de personas con heridas o enfermedades que afectan su sistema nervioso.
    \item Conectar a los seres humanos con la inteligencia artificial con el objetivo de que esta no nos deje atrás (Neuralink).
\end{itemize}

\section{Diseño}


\subsection{Requerimientos funcionales}

\begin{enumerate}
    \item Poder ser controlada remotamente
    \begin{enumerate}[label*=\arabic*.]
        \item Debe poder conectarse facilmente con plataformas que la puedan controlar \\
        \textbf{DP: Node-red}
        \item Poder conectarse a internet \\
        \textbf{DP: ESP32 WROOM}
    \end{enumerate}
    \item Poder sujetar objetos de distintos tamaños
    \textbf{DP: Motor acoplado a tornillo de potencia que mueve axialmente al hexagono de presion}
    \begin{enumerate}[label*=\arabic*.]
        \item Poder sostener una fuerza de 20N para sujetar al objeto.\\
        \textbf{DP: El motor, junto al sistema de transmisión de potencia}
        \item Se debe poder controlar la posición de la mano en su rango de movimiento con una precision suficiente como para ejercer presion sobre los objetos en su rango de sujeción.\\
        \textbf{DP: Motor stepper que con definición de 200 pasos por vuelta}
        \item Debe permitir mover el hexágono de presión linealmente sobre su recorrido.\\
        \textbf{DP: Eje de motor acoplado a tornillo de potencia cuyo carro esta sujeto al hexágono de presión}
        \begin{enumerate}[label*=\arabic*.]
            \item Debe sujetar al motor rotatoriamente sobre su eje, ejerciendo un apoyo para que el motor ejerza su torque.\\
            \textbf{DP: Hexagono acrilico en la base del motor} 
            \item Debe sujetar al motor y al sistema axialmente para que sobre el se delice el hexagono de presion y sin ejercer un troque en contra que trabe al motor.\\
            \textbf{DP: Rodamiento de sujeción axial que encaja en escalon en la parte superior final del eje}
            
        \end{enumerate}
        
    \end{enumerate}
    \item El diseño debe ser usable

    \textbf{DP: Interfaz de usuario de node-red (dashboard) e instrucciones de uso}
    \item El diseño debe ser repetible
    \textbf{DP: Repositorio con los archivos necesarios para reproducción y el informe del presente documento}
\end{enumerate}


\section{Análisis geométrico del mecanismo:}
El mecanismo esta conformado por 3 mecanismos de 4 barras. Los 3 se controlan por medio de dos eslabones y una pieza triangular al hexágono de presión, el cual tiene un recorrido de 3cm desde la posición superior hacia abajo. Esta conexión hace girar alrededor de su eje pinado al eslabón de entrada del mecanismo de 4 barras y por medio de esto logra su movimiento.

El eslabón biela (el que se sujeta en sus extremos a los eslabones que giran alrededor de sus conexiones pinadas) del mecanismo es la misma pata de agarre que sujeta al objeto. 
Al transladarse por el movimiento axial del hexagono presion, este eslabon dismuye su "altura" y se cierra sobre la posicion de agarre. De esta manera sujeta al objeto.


\subsection{Análisis relativo a la mano humana} 

Cutkosky, basándose en el trabajo de Napier, desarrollo una clasificacion de movimientos funcionalmente estudiando las poses de las manos de maquinistas en operaciones de manufactura. Segun Napier, la mano adquiere una posicion deacuerdo a lo que quiere lograr con el objeto. 

La poses de la mano se clasifican entonces posiciones de potencia y de precisión.

El mecanismo esta diseñado para permitir efectuar2 posiciones de precisión: trípode y esférica.

En lo seres humanos, el agarre trípode se utiliza para elevar objetos pequeños, pues es preciso. Además, los 3 dedos virtuales que componen el agarre permiten ejercer 3 puntos fuerza lateral y momentos, los cual lo hace ideal para sujetar el movimiento de un objeto en una trayectoria cuyas fuerzas están en dirección alrededor de los 360 grados del gripper. Un ejemplo en humanos de esta tarea es la escritura con lápiz o desenroscar un objeto sosteniendolo de 3 lugares con los dedos.

El agarre esferico tambien forma parte de los agarres de potencia. Por medio de tener un punto de apoyo directo en el marco de la maquina (o en el efector de mayor potencia como el braso en el caso humano), el movimiento realizado ahora puede involucrar mucha mayor fuerza, pues los dedos que rodean al objeto no estan haciendo empuje sino que estan haciendo fuerza en direccion radial para sujetar al objeto. De esta manera, se puede controlar el movimiento de un objeto con mayor potencia que con el agarre de tripode.

Ambos agarres también tienen la ventaja de permitir el agarre de objetos de distintas formas y tamaños, pues no solo se pueden sujetar objetos esfericos o cilindricos sino tambien objetos rectangulares o de forma irregular.

Solo con realizar un cambio en la posicion de sujecion en node-red, se puede ajustar el mecanismo para sujetar distintos objetos. 

%uso de iot: Recibir datos de utilizacion del producto para saber como esta. 
% Flexibilidad: Que por medio de unos cambios pueda pasar de ser una protesis a ser un brazo para proposito de investigacion.
% O en la plataforma.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{image.png}
    \caption{Orquidea que inicialmente es plana pero cambia su forma cuando entra en contacto con el agua \cite{youtube2}}
    \label{fig:my_label}
\end{figure}

\section{}

\section{KPIs de la mano:}

\subsection{Máxima carga sujetada-probeta:}
Tiene el objetivo de medir la capacidad de sujetar de la mano. Depende totalmente de la geometría del eslabón final de agarre y de el coeficiente de fricción de este con la pieza. \\


El procedimiento para se muestra a continuación. Este KPI esta medido respecto a una sola forma de probeta, con el material definido por el usuario de la mano. En este caso se utilizo un recipiente de plástico HDPE circular en el que se deposita la carga en el centro. 

\begin{enumerate}
    \item Se posiciona la mano directamente encima de la posición de agarre. De manera que solo se requiera un movimiento vertical para que la pieza quede entre las pinzas.
    \item Se baja la mano hasta la posición de sujeción en donde este el diámetro de sujeción de la probeta.
    \item Se realiza el movimiento de la mano hasta llegar a un punto cercano al objeto. Apartir de este punto, para el apriete, se realiza el movimiento del gripper con pasos discretos (enviando uno por uno). Se aprieta hasta antes de que el motor se deslice un paso. Si ya se deslizo, debe repetirse el apriete.
    \item Se eleva la mano verticalmente a una aceleración de menos de $1 cm/s^2$ hasta una altura de por lo menos 10cm.
    
\end{enumerate}

Si el anterior procedimiento fue exitoso, se toma el peso de la probeta utilizada como el valor de este KPI. Este KPI no solo consta del peso cargado sino también de la probeta utilizada (peso y forma).

Por esto se deben informar ambas informaciones al informar sobre este KPI.

\subsection{}
Este KPI busca medir la usabilidad de la mano, es decir, la facilidad con la que se puede realizar la función que desempeña. A este punto, la mano esta enfocada a poder hacer uso del sistema de actuación de la mano para hacer el testeo y verificación de este.\\
De esta forma, se define este KPI por medio de medir la cantidad de tiempo que le toma a una persona mover por primera vez la mano.

Metodología para la obtención de este KPI:

\begin{enumerate}
    \item La persona lee las instrucciones de utilización de la mano por completo.
    \item Se le indica a la persona que haga que el gripper se mueva y se toma el tiempo desde que se le indica esto hasta que mueve por primera vez la mano.
\end{enumerate}

Este KPI asume que la persona que lo utilizara es el laboratorista Juan Camilo de la universidad o cualquier persona que halla estudiado el pregardo en ingenieria Mecanica o Mecatronica que ya halla cursado los prerequisitos de la materia APM o materias equivalentes.

Tambien se asume que la persona sabe como acceder a node-red y tambien al dashboard de este.

\begin{itemize}
    \item 
\end{itemize}

\section{Gemelo digital}

El gemelo digital permite la simulación del mecanismo de la mano en su rango de movimiento. El método de reproducción de su geometría fue la medición de las medidas con calibrador con una resolución de 0.02mm. Los ángulos fueron medidos con el goniómetro disponible en el laboratorio con las medidas con una resolución de 1 grado.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{twin.png}
    \caption{Gemelo digital de la mano \cite{youtube2}}
    \label{fig:my_label}
\end{figure}

Así mismo el gemelo digital se verifico al imprimir las piezas en material PLA. Se encontraron desviaciones respecto a las dimensiones principales de \pm 1.3mm.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{dash.png}
    \caption{Interfaz de usuario node-red \cite{youtube2}}
    \label{fig:my_label}
\end{figure}

El gemelo digital permite la simulacion del movimiento del mecanismo, lo cual sera util para previsualizar el movimiento del actuador una vez armado.

\section{IIoT}

\subsection{Conexion wifi}

El ESP32 utiliza las credenciales de la red, nombre de la red y contraseña de esta, para conectarse al inicio de su funcionamiento.
Las credenciales se ingresan directamente en el codigo del ESP32.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{wifi.png}
    \caption{Conexion wifi}
    \label{fig:my_label}
\end{figure}

\subsection{Conexion MQTT}
El esquema de conexion se puede apreciar en el diagrama POA estatico. El ESP32 se conecta gracias a la libreria PubSubClient con el broker MQTT de hive. Alli crea un topico llamado StepperDMAOut y publica a este topico. Tambien se subsribe a un topico llamado stepperDMAin, a donde se envia la posicion del actuador.    

El servidor de Node-red, instaldo en alguna raspberry-pi o computador con conexion a internet, publica la informacion de posicion del actuador al topico stepperDMAin y se subscribe al topico stepperDMAout, del mismo borker Hive.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{conect.png}
    \caption{Codigo para conexion con broker}
    \label{fig:my_label}
\end{figure}

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{node.png}
    \caption{Diagrama de node-red utilizado para la conexion con el broker}
    \label{fig:my_label}
\end{figure}

La informacion del usuario se captura por medio de los nodos slider y numeric, los cuales representan componentes de la interfaz de usuario en el dashboard de nodered.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{node.png}
    \caption{Dashboard de node-red}
    \label{fig:my_label}
\end{figure}

La conexion con el broker MQTT se realiza por medio de los nodos receptor y publicador, los cuales utilizan la informacion de la direccion del broker, el nombre de los topicos y el puerto de este para realizar la conexion.

El dato enviado desde node red es la carga paga, la cual tiene el tipo de dato payload. Al llegar y salir del borker sale con tipo byte y en el ESP 32 se realiza su conversion a char y luego a int, para asi finalmentes ser utilizada como el numero de pasos que el motor dara desde su posicion de inicio.

La posicion de inicio corresponde a 0 pasos. Por esto la posicion del hexagono de presion debe comenzar desde el principio del recorrido del tornillo de potencia, en la parte superior.

\section{Electrónica y control del motor}

El circuito se compone del ESP32 y del driver del motor stepper. Tambien se utiliza un regulador de 5V para darle poder al ESP32, un capacitor de desacople para compensar cambios de corriente bruscos, y unos leds indicadores. Las borneras se utilizan para conectar con el motor y la bornera-conector para conectar la fuente de 12V.

El control del motor se realizo por medio de los pines step y dir. Una vez conectado el driver como se oberva en la figUra \cite{4988}, el pin step se debe conectar a algun GPIO del ESP32. Puede ser cualquiera pero se utilizo el GPIO 1. Cada vez que el motor da un paso, se envia un pulso por este pin. El pin dir se utiliza para controlar la direccion del motor. Tambien se puede conectar a cualquier GPIO pero se utilizo el GPIO 3.


\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{a4988.png}
    \caption{Esquema de conexión para el driver}
    \label{4988}
\end{figure}

El circuito se manufacturo per medio de serigrafia en PCB y los archivs de Kicad se encuentran disponbiles en el repositorio "stepper gripper" de github. 

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{squema.png}
    \caption{Esquematico del circuito}
    \label{fig:my_label}
\end{figure}

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{circu.png}
    \caption{Circuito en PCB}
    \label{fig:my_label}
\end{figure}

\section{Control del movimiento del motor}

El control de movimiento se realizo por medio de la libreria accelstepper de Arduino. 

Se debe instanciar una interfaz de stepper indicando los pines de pasos y dirección. \cite{int}

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{acc.png}
    \caption{Instanciación de interfaz para motor}
    \label{int}
\end{figure}

El setup del stepper se muestra en la figura \cite{in2}. 
Estos parametros se utilzran cuando sele solicite al motor alcanzar una posicion. setAcceleration configura la aceleracion para el perfil trapezoidal que siguie el stepper entre posicion y posicion. La velocidad maxima durante recorrido trapezoidal tambien se cofigura con setMaxSpeed.

setSpeed se utiliza para configurar la velocidad a la que el motor se movera cuando lo haga a velocidad constante sin aceleracion o desaceleracion.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{set.png}
    \caption{Establecimiento de parámetros iniciales para motor}
    \label{int2}
\end{figure}

El motor se controla en el ciclo loop por medio del codigo de la figura \ref{in3}. Requested position es la posicion solicitada y reachingPosition es la posición a la que se esta moviendo en ese momento en particular.
Si estas son distintas, se realiza el comando moveTo, el cual interrumpe el movimiento y hace que el motor inmediatamente comience a moverse hacia la posición señalada.

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{mot.png}
    \caption{Establecimiento de parámetros iniciales para motor}
    \label{in3}
\end{figure}



\section{Algoritmo de clasificación de señales}



\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{mot.png}
    \caption{Establecimiento de parámetros iniciales para motor}
    \label{in3}
\end{figure}

\begin{figure}[h]
    \centering
    \includegraphics[width = 7cm]{mot.png}
    \caption{Establecimiento de parámetros iniciales para motor}
    \label{in3}
\end{figure}


El algoritmo 


\section{Conclusiones:} \label{sec:metodologia} %10min

\begin{itemize}
    \item La manufactura aditiva es poderosa cuando es utilizada en conjunto con un gemelo digital por medio de permitir la reproducción exacta de la pieza y de esta forma desacoplando el proceso de prototipado del objeto real.
    \item Node-red facilita la conexión con protocolo MQTT con borkers, por medio de la representación intuitiva con nodos y flujos del sistema de información
    \item Los motores steppers facilitan el control de movimiento por medio de no requerir un sistema de feedback para controlar su posición y al permitir un torque sostenido.
\end{itemize}

\begin{itemize}
   
\end{itemize}
