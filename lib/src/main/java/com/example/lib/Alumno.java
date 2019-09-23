package com.example.lib;

public class Alumno extends Persona {

    public Alumno(String nombre, int edad){
        super(nombre,edad);
    }
    public void mostrar(){
        System.out.println("Soy el alumno "+ nombre);
        System.out.println("Y tengo "+ edad);
    }
}
