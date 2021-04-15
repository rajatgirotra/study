/**
 * The practice of creating properties in TS classes and assigning them in ctor is so common that TS created a shortcut for it.
 * You dont need to create properties any more. Just the constructor arguments can be prepended with the access specifier (like public below)
 * and TS will create the properties for you behind the scenes.
 */
export class Ingredient {
    constructor(public name: string, public amount: number) {
    }
}
