package com.example.lib;

import java.util.ArrayList;

public class MyClass {
    public static void main(String[] args) {
           /* String a[] = {"hola", "guapo", "que", "tal", "?"};

            String b[] = new String[2];
            b[0] = "hola";
            b[1] = "guapo";

            for (int i = 0; i < a.length; i++) {// for (String x : a){ System.out.println(x);}
                System.out.println(a[i]);
            }
            for (String x : b){
                System.out.println(x);
            }

            */

           /*
           ArrayList<String> a = new ArrayList<>();

           a.add("hola");
           a.add("guapo");
           for (String x : a){
            System.out.print(x + " ");
           }
            ArrayList<String> b = new ArrayList<>();
           for(String x : a ) {
               b.add(x.toUpperCase());
           }
            for(String x : b){
                System.out.print(x + " ");
            }

            */
           ArrayList<Persona> p = new ArrayList<>();
           p.add(new Alumno("David", 19));
           p.add(new Profesor("Paco",45));
           for(Persona x : p){
               //Este es el segundo cambio
               x.mostrar();
           }
    }
}
