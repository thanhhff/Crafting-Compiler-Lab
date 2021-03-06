/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object *obj);
void freeScope(Scope *scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab *symtab;
Type *intType;
Type *charType;

/******************* Type utilities ******************************/

Type *makeIntType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type *makeCharType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type *makeArrayType(int arraySize, Type *elementType)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type *duplicateType(Type *type)
{
  // TODO
  Type *type_copy = (Type *)malloc(sizeof(Type));
  type_copy->typeClass = type->typeClass;

  if (type->typeClass == TP_ARRAY)
  {
    type_copy->arraySize = type->arraySize;
    type_copy->elementType = duplicateType(type->elementType);
  }

  return type_copy;
}

int compareType(Type *type1, Type *type2)
{
  // TODO
  if (type1->typeClass == type2->typeClass)
  {
    if (type1->typeClass == TP_ARRAY)
    {
      if (type1->arraySize == type2->arraySize)
      {
        return compareType(type1->elementType, type2->elementType);
      }
      return 0;
    }
    return 1;
  }
  return 0;
}

void freeType(Type *type)
{
  // TODO
  switch (type->typeClass)
  {
  case TP_INT:
  case TP_CHAR:
    free(type);
    break;
  case TP_ARRAY:
    freeType(type->elementType);
    freeType(type);
    break;
  }
}

/******************* Constant utility ******************************/

ConstantValue *makeIntConstant(int i)
{
  // TODO
  ConstantValue *constVal = (ConstantValue *)malloc(sizeof(ConstantValue));
  constVal->type = TP_INT;
  constVal->intValue = i;
  return constVal;
}

ConstantValue *makeCharConstant(char ch)
{
  // TODO
  ConstantValue *constVal = (ConstantValue *)malloc(sizeof(ConstantValue));
  constVal->type = TP_CHAR;
  constVal->charValue = ch;
  return constVal;
}

ConstantValue *duplicateConstantValue(ConstantValue *v)
{
  // TODO
  ConstantValue *constVal_copy = (ConstantValue *)malloc(sizeof(ConstantValue));
  constVal_copy->type = v->type;
  if (constVal_copy->type == TP_CHAR)
  {
    constVal_copy->charValue = v->charValue;
  }
  else if (constVal_copy->type == TP_INT)
  {
    constVal_copy->intValue = v->intValue;
  }
  return constVal_copy;
}

/******************* Object utilities ******************************/

Scope *createScope(Object *owner, Scope *outer)
{
  Scope *scope = (Scope *)malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object *createProgramObject(char *programName)
{
  Object *program = (Object *)malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes *)malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program, NULL);
  symtab->program = program;

  return program;
}

Object *createConstantObject(char *name)
{
  // TODO
  Object *constant = (Object *)malloc(sizeof(Object));
  strcpy(constant->name, name);
  constant->kind = OBJ_CONSTANT;
  constant->constAttrs = (ConstantAttributes *)malloc(sizeof(ConstantAttributes));
  constant->constAttrs->value = NULL;

  return constant;
}

Object *createTypeObject(char *name)
{
  // TODO
  Object *typeObject = (Object *)malloc(sizeof(Object));
  strcpy(typeObject->name, name);
  typeObject->kind = OBJ_TYPE;
  typeObject->typeAttrs = (TypeAttributes *)malloc(sizeof(TypeAttributes));
  typeObject->typeAttrs->actualType = NULL;

  return typeObject;
}

Object *createVariableObject(char *name)
{
  // TODO
  Object *variableObject = (Object *)malloc(sizeof(Object));
  strcpy(variableObject->name, name);
  variableObject->kind = OBJ_VARIABLE;
  variableObject->varAttrs = (VariableAttributes *)malloc(sizeof(VariableAttributes));
  variableObject->varAttrs->scope = symtab->currentScope;
  variableObject->varAttrs->type = NULL;

  return variableObject;
}

Object *createFunctionObject(char *name)
{
  // TODO
  Object *functionObject = (Object *)malloc(sizeof(Object));
  strcpy(functionObject->name, name);
  functionObject->kind = OBJ_FUNCTION;
  functionObject->funcAttrs = (FunctionAttributes *)malloc(sizeof(FunctionAttributes));
  functionObject->funcAttrs->scope = createScope(functionObject, symtab->currentScope);
  functionObject->funcAttrs->paramList = NULL;
  functionObject->funcAttrs->returnType = NULL;
  return functionObject;
}

Object *createProcedureObject(char *name)
{
  // TODO
  Object *procedureObject = (Object *)malloc(sizeof(Object));
  strcpy(procedureObject->name, name);
  procedureObject->kind = OBJ_PROCEDURE;
  procedureObject->procAttrs = (ProcedureAttributes *)malloc(sizeof(ProcedureAttributes));
  procedureObject->procAttrs->paramList = NULL;
  procedureObject->procAttrs->scope = createScope(procedureObject, symtab->currentScope);
  return procedureObject;
}

Object *createParameterObject(char *name, enum ParamKind kind, Object *owner)
{
  // TODO
  Object *parameterObject = (Object *)malloc(sizeof(Object));
  strcpy(parameterObject->name, name);
  parameterObject->kind = OBJ_PARAMETER;

  parameterObject->paramAttrs = (ParameterAttributes *)malloc(sizeof(ParameterAttributes));

  parameterObject->paramAttrs->kind = kind;
  parameterObject->paramAttrs->function = owner;
  parameterObject->paramAttrs->type = NULL;
  return parameterObject;
}

void freeObject(Object *obj)
{
  switch (obj->kind)
  {
  case OBJ_CONSTANT:
    free(obj->constAttrs->value);
    free(obj->constAttrs);
    break;
  case OBJ_TYPE:
    free(obj->typeAttrs->actualType);
    free(obj->typeAttrs);
    break;
  case OBJ_VARIABLE:
    free(obj->varAttrs->type);
    free(obj->varAttrs);
    break;
  case OBJ_FUNCTION:
    freeReferenceList(obj->funcAttrs->paramList);
    freeType(obj->funcAttrs->returnType);
    freeScope(obj->funcAttrs->scope);
    free(obj->funcAttrs);
    break;
  case OBJ_PROCEDURE:
    freeReferenceList(obj->procAttrs->paramList);
    freeScope(obj->procAttrs->scope);
    free(obj->procAttrs);
    break;
  case OBJ_PROGRAM:
    freeScope(obj->progAttrs->scope);
    free(obj->progAttrs);
    break;
  case OBJ_PARAMETER:
    freeType(obj->paramAttrs->type);
    free(obj->paramAttrs);
  }
  free(obj);
}

void freeScope(Scope *scope)
{
  freeObjectList(scope->objList);
  free(scope);
}

void freeObjectList(ObjectNode *objList)
{
  ObjectNode *list = objList;

  while (list != NULL)
  {
    ObjectNode *node = list;
    list = list->next;
    freeObject(node->object);
    free(node);
  }
}

void freeReferenceList(ObjectNode *objList)
{
  ObjectNode *list = objList;

  while (list != NULL)
  {
    ObjectNode *node = list;
    list = list->next;
    free(node);
  }
}

void addObject(ObjectNode **objList, Object *obj)
{
  ObjectNode *node = (ObjectNode *)malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL)
    *objList = node;
  else
  {
    ObjectNode *n = *objList;
    while (n->next != NULL)
      n = n->next;
    n->next = node;
  }
}

Object *findObject(ObjectNode *objList, char *name)
{
  // TODO
  ObjectNode *current = objList;
  if (current != NULL)
  {
    if (strcmp(current->object->name, name) == 0)
    {
      return current->object;
    }
    current = current->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void)
{
  Object *obj;
  Object *param;

  symtab = (SymTab *)malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;

  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void)
{
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope *scope)
{
  symtab->currentScope = scope;
}

void exitBlock(void)
{
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object *obj)
{
  if (obj->kind == OBJ_PARAMETER)
  {
    Object *owner = symtab->currentScope->owner;
    switch (owner->kind)
    {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }

  addObject(&(symtab->currentScope->objList), obj);
}
