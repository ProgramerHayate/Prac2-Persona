package com.example.lib;

public class Persona {
    protected int edad;
    protected String nombre;

    public Persona(String nombre, int edad) {
        this.edad =edad;
        this.nombre=nombre;
    }

    public int getEdad() {
        return edad;
    }

    public String getNombre() {
        return nombre;
    }

    public void mostrar() {
        System.out.println("Me llamo "+ nombre);
        System.out.println("Tengo "+ edad);
    }
}
