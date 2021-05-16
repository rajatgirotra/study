import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'filter',
  pure: false
})
export class FilterPipe implements PipeTransform {

  transform(value, filterString: string, filterOn: string): unknown {
    if (value.length === 0 || filterString === '') {
      return value;
    } else {
      const returnArray = [];
      for (const val of value) {
        if (val[filterOn] === filterString) {
          returnArray.push(val);
        }
      }
      return returnArray;
    }
  }
}

/**
 * what is pure: false? By default a pipe will not re-apply if the underlying data changes. That's because it can cause a lot of
 * performance reasons. But if you want that behavior, you need to set pure: false
 *
 * See what happens if you are filtering on let say 'stable' and then you hit 'Add Server' multiple times.
 */
