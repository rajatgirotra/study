add_executable(inhertiance_and_composition_composition Composition.cpp)
target_link_libraries(inhertiance_and_composition_composition PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_inheritance Inheritance.cpp)
target_link_libraries(inhertiance_and_composition_inheritance PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_composition2 Composition2.cpp)
target_link_libraries(inhertiance_and_composition_composition2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_combined Combined.cpp)
target_link_libraries(inhertiance_and_composition_combined PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_upcasting Upcasting.cpp)
target_link_libraries(inhertiance_and_composition_upcasting PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_car Car.cpp)
target_link_libraries(inhertiance_and_composition_car PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_simple1 Simple_1.cpp)
target_link_libraries(inhertiance_and_composition_simple1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_simple2 Simple_2.cpp)
target_link_libraries(inhertiance_and_composition_simple2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_simple3 Simple_3.cpp)
target_link_libraries(inhertiance_and_composition_simple3 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_simple4 Simple_4.cpp)
target_link_libraries(inhertiance_and_composition_simple4 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_simple5 Simple_5.cpp)
target_link_libraries(inhertiance_and_composition_simple5 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_copy_ctor CopyConstructor.cpp)
target_link_libraries(inhertiance_and_composition_copy_ctor PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_order Order.cpp)
target_link_libraries(inhertiance_and_composition_order PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_name_hiding NameHiding.cpp)
target_link_libraries(inhertiance_and_composition_name_hiding PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_fname1 FName1.cpp)
target_link_libraries(inhertiance_and_composition_fname1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_fname2 FName2.cpp)
target_link_libraries(inhertiance_and_composition_fname2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_redefining_overloaded_functions Redefining_Overloaded_functions.cpp)
target_link_libraries(inhertiance_and_composition_redefining_overloaded_functions PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_operator_inheritance OperatorInheritance.cpp)
target_link_libraries(inhertiance_and_composition_operator_inheritance PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_pseudo_ctor PseudoConstructor.cpp)
target_link_libraries(inhertiance_and_composition_pseudo_ctor PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_protected Protected.cpp)
target_link_libraries(inhertiance_and_composition_protected PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_private_inheritance PrivateInheritance.cpp)
target_link_libraries(inhertiance_and_composition_private_inheritance PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_public_private_protected Public_private_Protected.cpp)
target_link_libraries(inhertiance_and_composition_public_private_protected PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(inhertiance_and_composition_synthesized_functions SynthesizedFunctions.cpp)
target_link_libraries(inhertiance_and_composition_synthesized_functions PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)
