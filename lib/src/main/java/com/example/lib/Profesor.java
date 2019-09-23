package com.example.lib;

public class Profesor extends Persona {

    public Profesor(String nombre, int edad){
        super(nombre,edad);
    }

    public void mostrar(){
        System.out.println("Soy el profesor "+ nombre);
        System.out.println("Y tengo "+ edad);
    }
}
