import { AbstractControl} from '@angular/forms';

export function searchValidator(control: AbstractControl) {
    const specialRegexp: RegExp = /[@#$%^&*()_+\=\[\]{};"\\|,.<>\/]/;
  if (control.value && specialRegexp.test(control.value)) {
    return { searchValid: true };
  }
  return null;
}