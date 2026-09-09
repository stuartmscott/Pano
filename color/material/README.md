# Material Color

A color palette inspired by [Material Design](https://material.io).

## Usage

Use `Significance::Primary` for controls/interactable elements, `Significance::Secondary` for aesthetic/design elements, `Significance::Text` for legibility, and `Significance::Normal` for the rest.

### Mode
```
// Light Mode
app.AddColorProvider(CreateLightMaterialColorProvider());
// Dark Mode
app.AddColorProvider(CreateDarkMaterialColorProvider());
```

