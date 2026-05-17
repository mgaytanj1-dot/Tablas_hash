import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

    static class Estudiante {

        int studentId;
        String fullName;
        String career;
        int semester;
        double gpa;
        int skillScore;

        public Estudiante(
                int studentId,
                String fullName,
                String career,
                int semester,
                double gpa,
                int skillScore
        ) {

            this.studentId = studentId;
            this.fullName = fullName;
            this.career = career;
            this.semester = semester;
            this.gpa = gpa;
            this.skillScore = skillScore;
        }

        @Override
        public String toString() {

            return "ID: " + studentId +
                    "\nNombre: " + fullName +
                    "\nCarrera: " + career +
                    "\nSemestre: " + semester +
                    "\nGPA: " + gpa +
                    "\nSkill Score: " + skillScore;
        }
    }

    public static void main(String[] args) {

        System.out.println("=====================================");
        System.out.println("Nombre: Marco Gaytan");
        System.out.println("Carnet: 9941249182");
        System.out.println("=====================================");

        HashMap<Integer, Estudiante> estudiantes = new HashMap<>();

        Scanner sc = new Scanner(System.in);

        int opcion;

        do {

            System.out.println("\n========== MENU ==========");
            System.out.println("1. Agregar estudiante");
            System.out.println("2. Cargar CSV");
            System.out.println("3. Buscar estudiante");
            System.out.println("4. Eliminar estudiante");
            System.out.println("5. Mostrar estudiantes");
            System.out.println("6. Mostrar estadisticas");
            System.out.println("7. Salir");

            System.out.print("Seleccione opcion: ");

            opcion = sc.nextInt();

            // AGREGAR ESTUDIANTE
            if (opcion == 1) {

                System.out.print("ID: ");
                int id = sc.nextInt();

                sc.nextLine();

                if (estudiantes.containsKey(id)) {

                    System.out.println("Ya existe un estudiante con ese ID.");
                    continue;
                }

                System.out.print("Nombre completo: ");
                String nombre = sc.nextLine();

                System.out.print("Carrera: ");
                String carrera = sc.nextLine();

                System.out.print("Semestre: ");
                int semestre = sc.nextInt();

                System.out.print("GPA: ");
                double gpa = sc.nextDouble();

                System.out.print("Skill Score: ");
                int skill = sc.nextInt();

                Estudiante estudiante = new Estudiante(
                        id,
                        nombre,
                        carrera,
                        semestre,
                        gpa,
                        skill
                );

                estudiantes.put(id, estudiante);

                System.out.println("Estudiante agregado correctamente.");
            }

            // CARGAR CSV
            else if (opcion == 2) {

                try {

                    BufferedReader br = new BufferedReader(
                            new FileReader("estudiantes.csv")
                    );

                    String linea;

                    // Saltar encabezado
                    br.readLine();

                    while ((linea = br.readLine()) != null) {

                        String[] datos = linea.split(",");

                        int studentId = Integer.parseInt(datos[0]);

                        if (estudiantes.containsKey(studentId)) {

                            System.out.println(
                                    "Estudiante duplicado: " + studentId
                            );

                            continue;
                        }

                        String fullName = datos[1];
                        String career = datos[2];
                        int semester = Integer.parseInt(datos[3]);
                        double gpa = Double.parseDouble(datos[4]);
                        int skillScore = Integer.parseInt(datos[5]);

                        Estudiante estudiante = new Estudiante(
                                studentId,
                                fullName,
                                career,
                                semester,
                                gpa,
                                skillScore
                        );

                        estudiantes.put(studentId, estudiante);
                    }

                    br.close();

                    System.out.println("CSV cargado correctamente.");

                } catch (Exception e) {

                    System.out.println("Error al leer CSV.");
                }
            }

            // BUSCAR
            else if (opcion == 3) {

                System.out.print("Ingrese ID: ");

                int id = sc.nextInt();

                if (estudiantes.containsKey(id)) {

                    System.out.println(
                            "\n=== ESTUDIANTE ENCONTRADO ==="
                    );

                    System.out.println(estudiantes.get(id));

                } else {

                    System.out.println("No encontrado.");
                }
            }

            // ELIMINAR
            else if (opcion == 4) {

                System.out.print("Ingrese ID a eliminar: ");

                int id = sc.nextInt();

                if (estudiantes.containsKey(id)) {

                    estudiantes.remove(id);

                    System.out.println(
                            "Estudiante eliminado."
                    );

                } else {

                    System.out.println(
                            "No existe estudiante."
                    );
                }
            }

            // MOSTRAR ESTUDIANTES
            else if (opcion == 5) {

                System.out.println(
                        "\n=== ESTUDIANTES ==="
                );

                if (estudiantes.isEmpty()) {

                    System.out.println("No hay estudiantes cargados.");
                }

                for (Integer key : estudiantes.keySet()) {

                    System.out.println("-------------------");

                    System.out.println(estudiantes.get(key));
                }
            }

            // ESTADISTICAS
            else if (opcion == 6) {

                System.out.println(
                        "\n=== ESTADISTICAS ==="
                );

                System.out.println(
                        "Total estudiantes: "
                                + estudiantes.size()
                );

                System.out.println(
                        "Estructura usada: HashMap<Integer, Estudiante>"
                );

                System.out.println(
                        "Implementacion usando estructura nativa HashMap de Java."
                );
            }

            else if (opcion == 7) {

                System.out.println("Saliendo del programa...");
            }

            else {

                System.out.println("Opcion invalida.");
            }

        } while (opcion != 7);

        sc.close();
    }
}
