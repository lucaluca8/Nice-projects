import { AbstractControl} from '@angular/forms';

export function nameValidator(control: AbstractControl) {
  if (control.value?.length>16 && control.value) {
    return { nameValid: true };
  }
  return null;
}

export function specialCharactersValidator(control: AbstractControl) {
  const specialRegexp: RegExp = /[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/;
  if (specialRegexp.test(control.value) && control.value) {
    return { specialValid: true };
  }
  return null;
}

export function emailValidator(control: AbstractControl) {
  const specialRegexp: RegExp = /^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$/;
  if (!specialRegexp.test(control.value) && control.value) {
    return { emailValid: true };
  }
  return null;
}

export function passwordContentsValidator(control: AbstractControl) {
  const specialRegexp: RegExp = /^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])[a-zA-Z0-9]+$$/;
  if (!specialRegexp.test(control.value)&& control.value) {
    return { passContValid: true };
  }
  return null;
}





