#include "usuarios.h"



//-----------------FUNCIONES DE ARREGLO DE USUARIOS---------------

//crea un arreglo de usuarios con el tamaño justo, carga los usuarios e inicializa en NULL su lista de canciones
//devuelve el arreglo
stCelda *pasarUserToADL(int cantUsers)
{
    int i=0;
    stCelda *arreglo = (stCelda*) malloc(sizeof(stCelda)*cantUsers);
    FILE *ArchivoUser = fopen(ARCHIVO_USUARIOS, "rb");
    stUsuario aux;
    if (ArchivoUser!=NULL)
    {
        while(fread(&aux, sizeof(stUsuario),1,ArchivoUser)>0)
        {
            arreglo[i].usr = aux;
            arreglo[i].listaCanciones = NULL;
            i++;
        }
        fclose(ArchivoUser);
    }
    return arreglo;
}


//agrega un usuario al final del arreglo
stCelda * agregarUsuario(stUsuario user, stCelda * arr, int ** validos)
{
    //user.idUsuario = (*validos);      //lo hace el menu de alta

    stCelda * arr_copia = malloc(sizeof(stCelda)*(**validos + 1));

    for(int i=0 ; i<(**validos) ; i++)
    {
        arr_copia[i] = arr[i];
    }

    arr_copia[**validos].usr = user;

    **validos += 1;

    ADU_to_archivoUsers(arr, *validos);

    return arr_copia;
}

void ADU_to_archivoUsers(stCelda * array_de_usuarios, int * validos)
{
    FILE * archivoUsers = fopen(ARCHIVO_USUARIOS, "wb");

    if(archivoUsers != NULL)
    {
        for(int i = 0 ; i < *validos ; i++)
        {
            fwrite(&(array_de_usuarios[i].usr), sizeof(stUsuario), 1, archivoUsers);
        }
    }

    fclose(archivoUsers);
}


//busca un user en el arreglo por id y devuelve la posicion, devuelve -1 si no lo encontro
int buscarUsuarioPorId(int idUser, stCelda a[], int validos)
{
    int pos = -1; //default si no lo encuentra

    for(int i=0 ; i<validos ; i++)
    {
        if(a[i].usr.idUsuario == idUser && a[i].usr.eliminado == 0)
        {
            pos = i;
        }
    }
    return pos;
}

//busca un user en el arreglo por nombre y devuelve la posicion, devuelve -1 si no lo encontro
int buscarUsuarioPorNombre(char nombre[30], stCelda *a, int validos)
{
    int pos = -1; //default si no lo encuentra

    for(int i=0 ; i<validos ; i++)
    {
        stUsuario aux = a[i].usr;
        if( strcmp( nombre, (aux.nombreUsuario) ) == 0  &&  (aux.eliminado) == 0)
        {
            pos = i;
        }
    }
    return pos;
}


void mostrarUsuariosAndCanciones(stCelda a[], int validos)
{
    for(int i=0 ; i<validos ; i++)
    {
        printf("\n\nusuario: %s\n\ncanciones escuchadas:\n\n", a[i].usr.nombreUsuario);
        mostrarLC(a[i].listaCanciones);
    }
}











//---------------FUNCIONES DE ESTRUCTURA DE USUARIOS------------

//checkea si existe el archivo de usuarios, si no existe, crea el archivo de usuarios con un admin default en el id 0
void inicArchivoUsuarios()
{
    FILE * archi;

    if( (archi = fopen(ARCHIVO_USUARIOS, "rb")) == NULL ) //si el archivo no existe
    {
        /*if ( (archi = fopen(ARCHIVO_USUARIOS, "wb")) == NULL )    //lo crea, si da NULL no lo pudo crear y muestra el mensaje
        {
            printf("\nerror creando el archivo\n");
        }
        else
        {*/
        //crear primer usuario (admin default)

        stUsuario adminDefault;
        //adminDefault = crearUsuario();

        adminDefault.idUsuario = 0;
        adminDefault.anioNacimiento = 0;
        adminDefault.genero = 'M';
        strcpy(adminDefault.pais, "Argentina");
        adminDefault.esAdmin = 1;
        strcpy( adminDefault.nombreUsuario, "admin" );
        strcpy( adminDefault.pass, "admin" );
        adminDefault.eliminado=0;

        if(guardarUsuarioArchivo(adminDefault) == 0)
            printf("\nerror creando admin default\n");

        //}
    }
    fclose(archi);
}



//inicializa una estructura usuario en NULL
stUsuario crearUsuario()
{
    stUsuario aux;

    aux.idUsuario = -1;
    strcpy( aux.nombreUsuario, "NULL" );
    strcpy( aux.pass, "NULL" );
    aux.anioNacimiento = 0;
    aux.genero = 'n';
    strcpy( aux.pais, "NULL" );
    aux.eliminado = 0;
    aux.esAdmin = 0;

    return aux;

    //return NULL;
}


//guarda un usuario, en el archivo de usuarios, devuelve 1 si lo guardo
int guardarUsuarioArchivo(stUsuario usuario)
{
    FILE * archi = fopen(ARCHIVO_USUARIOS, "ab");
    int guardado = 0;

    if(archi != NULL)
    {
        if( fwrite(&usuario, sizeof(stUsuario), 1, archi) != 1)
        {
            printf("error guardando el usuario");
        }
        else
        {
            guardado = 1;
        }
    }

    fclose(archi);

    return guardado;
}


//cuenta la cantidad de usuarios en el archivo
int cantUsuarios()
{
    FILE * archi = fopen(ARCHIVO_USUARIOS, "rb");

    int cantUsuarios = 0;

    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantUsuarios = ftell(archi)/sizeof(stUsuario);
    }

    fclose(archi);

    return cantUsuarios;
}



//recibe el nombre del usuario, devuelvYA ESTÁ HECHA

/*int buscarUsuario(char nombre[], stCelda a[], int validos)
{
    stUsuario aux;
    aux = crearUsuario();
    int encontrado = 0;

    printf("\n\n%s\n\n", nombre);   //hasta aca va bien


    FILE * archi = fopen(ARCHIVO_USUARIOS, "rb");

    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux, sizeof(stUsuario), 1, archi) == 1)
        {
            if ( strcmp(aux.nombreUsuario, nombre) == 0 )   //&& aux.eliminado == 0 ?
            {
                encontrado = 1;
            }
        }
    }
    else
    {
        printf("\nerror al abrir el archivo\n");
    }

    fclose(archi);

    return aux;
}*/



//devuelve la estructura del ultimo usuario del archivo o devuelve una estructura NULL si no existen usuarios
stUsuario ultimoUserIngresado()
{
    FILE * archi = fopen(ARCHIVO_USUARIOS, "rb");
    stUsuario aux = crearUsuario();

    if(archi != NULL)
    {
        fseek(archi, (-1)*sizeof(stUsuario), SEEK_END);
        fread(&aux, sizeof(stUsuario), 1, archi);
    }

    fclose(archi);

    return aux;
}



//hace la baja lógica de un usuario, devuelve 1 si fue exitoso
int borrarUsuario(stUsuario usuario)
{
    FILE * archi = fopen(ARCHIVO_USUARIOS, "rb+");
    int borrado = 0;

    if(archi != NULL)
    {
        usuario.eliminado = 1;
        fseek(archi, (usuario.idUsuario)*sizeof(stUsuario), SEEK_SET);
        fwrite(&usuario, sizeof(stUsuario), 1, archi);

        //comprobación
        fseek(archi, (-1)*sizeof(stUsuario), SEEK_CUR);
        fread(&usuario, sizeof(stUsuario), 1, archi);
        if (usuario.eliminado == 1)
        {
            borrado = 1;
        }

    }

    fclose(archi);

    return borrado;
}


void mostrarUsuario(stUsuario usuario)
{
    printf("usuario: %s\na%co de nacimiento: %i\n", usuario.nombreUsuario, ENIEMINUSCULA, usuario.anioNacimiento);
    printf("genero: %c\npais: ", usuario.genero);
    puts(usuario.pais);
    printf("id: %i\neliminado: %i\nes admin: %i\npass: %s\n\n", usuario.idUsuario, usuario.eliminado, usuario.esAdmin, usuario.pass);
}

/*stCelda *pasarUserToADL(int validos){ ///Validos viene de cantUsuarios();
    int i=0;
    stCelda *arreglo = malloc(sizeof(stCelda)*validos);
    FILE *ArchivoUser = fopen(ARCHIVO_USUARIOS, "rb");
    while(fread(&arreglo[i].usr, sizeof(stUsuario),1,ArchivoUser)>0){
        arreglo[i].listaCanciones = NULL;
        i++;
    }
    fclose(ArchivoUser);
    return arreglo;
}*/
