package io.swagger.codegen.languages;

import com.google.common.base.CaseFormat;
import com.samskivert.mustache.Mustache;
import com.samskivert.mustache.Template;
import io.swagger.codegen.*;
import io.swagger.models.ModelImpl;
import io.swagger.models.properties.*;
import org.apache.commons.lang3.StringUtils;

import java.io.File;
import java.io.IOException;
import java.io.StringWriter;
import java.io.Writer;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.Map;

public class TypeScriptAngular2ClientCodegen extends AbstractTypeScriptClientCodegen {
    private static final SimpleDateFormat SNAPSHOT_SUFFIX_FORMAT = new SimpleDateFormat("yyyyMMddHHmm");

    public static final String NPM_NAME = "npmName";
    public static final String NPM_VERSION = "npmVersion";
    public static final String NPM_REPOSITORY = "npmRepository";
    public static final String SNAPSHOT = "snapshot";
    public static final String USE_OPAQUE_TOKEN = "useOpaqueToken";
    public static final String INJECTION_TOKEN = "injectionToken";
    public static final String WITH_INTERFACES = "withInterfaces";

    protected String npmName = null;
    protected String npmVersion = "1.0.0";
    protected String npmRepository = null;
    protected String injectionToken = "InjectionToken<string>";

    public TypeScriptAngular2ClientCodegen() {
        super();
        this.outputFolder = "generated-code/typescript-angular2";

        embeddedTemplateDir = templateDir = "typescript-angular2";
        modelTemplateFiles.put("model.mustache", ".ts");
        apiTemplateFiles.put("effects.mustache", ".effects.ts");
        typeMapping.put("Date","Date");
        apiPackage = "";
        modelPackage = "model";

        additionalProperties.put("fnSnakeCase", new SnakeCaseLambda());
        additionalProperties.put("fnCapitalize", new CapitalizeLambda());

        this.cliOptions.add(new CliOption(NPM_NAME, "The name under which you want to publish generated npm package"));
        this.cliOptions.add(new CliOption(NPM_VERSION, "The version of your npm package"));
        this.cliOptions.add(new CliOption(NPM_REPOSITORY, "Use this property to set an url your private npmRepo in the package.json"));
        this.cliOptions.add(new CliOption(SNAPSHOT, "When setting this property to true the version will be suffixed with -SNAPSHOT.yyyyMMddHHmm", BooleanProperty.TYPE).defaultValue(Boolean.FALSE.toString()));
        this.cliOptions.add(new CliOption(USE_OPAQUE_TOKEN, "When setting this property to true, OpaqueToken is used instead of InjectionToken", BooleanProperty.TYPE).defaultValue(Boolean.FALSE.toString()));
        this.cliOptions.add(new CliOption(WITH_INTERFACES, "Setting this property to true will generate interfaces next to the default class implementations.", BooleanProperty.TYPE).defaultValue(Boolean.FALSE.toString()));
    }

    @Override
    public String apiFilename(String templateName, String tag) {
        String suffix = apiTemplateFiles().get(templateName);
        return apiFileFolder() + '/' + StringUtils.lowerCase(tag) + suffix;
    }

    @Override
    protected void addAdditionPropertiesToCodeGenModel(CodegenModel codegenModel, ModelImpl swaggerModel) {
        codegenModel.additionalPropertiesType = getSwaggerType(swaggerModel.getAdditionalProperties());
        addImport(codegenModel, codegenModel.additionalPropertiesType);
    }

    @Override
    public String getName() {
        return "typescript-angular2";
    }

    @Override
    public String getHelp() {
        return "Generates a TypeScript Angular2 client library.";
    }

    @Override
    public void processOpts() {
        super.processOpts();
        supportingFiles.add(new SupportingFile("models.mustache", modelPackage().replace('.', File.separatorChar), "models.ts"));
        supportingFiles.add(new SupportingFile("index.mustache", getIndexDirectory(), "index.ts"));
        supportingFiles.add(new SupportingFile("configuration.mustache", getIndexDirectory(), "configuration.ts"));
        supportingFiles.add(new SupportingFile("actions.mustache",  apiPackage().replace('.', File.separatorChar), "actions.ts"));

        if(additionalProperties.containsKey(NPM_NAME)) {
            addNpmPackageGeneration();
        }

        if(additionalProperties.containsKey(USE_OPAQUE_TOKEN) && Boolean.valueOf(additionalProperties.get(USE_OPAQUE_TOKEN).toString())) {
            this.setOpaqueToken();
        }
        additionalProperties.put(INJECTION_TOKEN, this.injectionToken);

        if(additionalProperties.containsKey(WITH_INTERFACES)) {
            boolean withInterfaces = Boolean.parseBoolean(additionalProperties.get(WITH_INTERFACES).toString());
            if (withInterfaces) {
                apiTemplateFiles.put("apiInterface.mustache", "Interface.ts");
            }
        }
    }

    private void addNpmPackageGeneration() {
        if(additionalProperties.containsKey(NPM_NAME)) {
            this.setNpmName(additionalProperties.get(NPM_NAME).toString());
        }

        if (additionalProperties.containsKey(NPM_VERSION)) {
            this.setNpmVersion(additionalProperties.get(NPM_VERSION).toString());
        }

        if (additionalProperties.containsKey(SNAPSHOT) && Boolean.valueOf(additionalProperties.get(SNAPSHOT).toString())) {
            this.setNpmVersion(npmVersion + "-SNAPSHOT." + SNAPSHOT_SUFFIX_FORMAT.format(new Date()));
        }
        additionalProperties.put(NPM_VERSION, npmVersion);

        if (additionalProperties.containsKey(NPM_REPOSITORY)) {
            this.setNpmRepository(additionalProperties.get(NPM_REPOSITORY).toString());
        }

    }

    private String getIndexDirectory() {
        String indexPackage = modelPackage.substring(0, Math.max(0, modelPackage.lastIndexOf('.')));
        return indexPackage.replace('.', File.separatorChar);
    }

    @Override
    public String getTypeDeclaration(Property p) {
        Property inner;
        if(p instanceof ArrayProperty) {
            ArrayProperty mp1 = (ArrayProperty)p;
            inner = mp1.getItems();
            return this.getSwaggerType(p) + "<" + this.getTypeDeclaration(inner) + ">";
        } else if(p instanceof MapProperty) {
            MapProperty mp = (MapProperty)p;
            inner = mp.getAdditionalProperties();
            return "{ [key: string]: " + this.getTypeDeclaration(inner) + "; }";
        } else if(p instanceof FileProperty || p instanceof ObjectProperty) {
            return "any";
        } else {
            return super.getTypeDeclaration(p);
        }
    }

    @Override
    public String getSwaggerType(Property p) {
        String swaggerType = super.getSwaggerType(p);
        if(isLanguagePrimitive(swaggerType) || isLanguageGenericType(swaggerType)) {
            return swaggerType;
        }
        return addModelPrefix(swaggerType);
    }

    private String addModelPrefix(String swaggerType) {
        String type = null;
        if (typeMapping.containsKey(swaggerType)) {
            type = typeMapping.get(swaggerType);
        } else {
            type = swaggerType;
        }

        if (!isLanguagePrimitive(type) && !isLanguageGenericType(type)) {
            type = "Models." + swaggerType;
        }
        return type;
    }

    private boolean isLanguagePrimitive(String type) {
        return languageSpecificPrimitives.contains(type);
    }

    private boolean isLanguageGenericType(String type) {
        for (String genericType: languageGenericTypes) {
            if (type.startsWith(genericType + "<"))  {
                return true;
            }
        }
        return false;
    }

    @Override
    public void postProcessParameter(CodegenParameter parameter) {
        super.postProcessParameter(parameter);
        parameter.dataType = addModelPrefix(parameter.dataType);
    }

    @Override
    public Map<String, Object> postProcessOperations(Map<String, Object> operations) {
        Map<String, Object> objs = (Map<String, Object>) operations.get("operations");
        List<CodegenOperation> ops = (List<CodegenOperation>) objs.get("operation");
        for (CodegenOperation op : ops) {
            // Convert httpMethod to Angular's RequestMethod enum
            // https://angular.io/docs/ts/latest/api/http/index/RequestMethod-enum.html
            switch (op.httpMethod.toUpperCase()) {
                case "GET":
                    op.httpMethod = "RequestMethod.GET";
                    break;
                case "POST":
                    op.httpMethod = "RequestMethod.POST";
                    break;
                case "PUT":
                    op.httpMethod = "RequestMethod.PUT";
                    break;
                case "DELETE":
                    op.httpMethod = "RequestMethod.DELETE";
                    break;
                case "OPTIONS":
                    op.httpMethod = "RequestMethod.OPTIONS";
                    break;
                case "HEAD":
                    op.httpMethod = "RequestMethod.HEAD";
                    break;
                case "PATCH":
                    op.httpMethod = "RequestMethod.PATCH";
                    break;
                default:
                    throw new RuntimeException("Unknown HTTP Method " + op.httpMethod + " not allowed");
            }

            // Convert path to TypeScript template string
            op.path = op.path.replaceAll("\\{(.*?)\\}", "\\$\\{$1\\}");
        }

        return operations;
    }

    private static abstract class CustomLambda implements Mustache.Lambda {
        @Override
        public void execute(Template.Fragment frag, Writer out) throws IOException {
            final StringWriter tempWriter = new StringWriter();
            frag.execute(tempWriter);
            out.write(formatFragment(tempWriter.toString()));
        }

        public abstract String formatFragment(String fragment);
    }

    private static class SnakeCaseLambda extends CustomLambda {

        public SnakeCaseLambda() {}

        @Override
        public String formatFragment(String fragment) {
            return CaseFormat.LOWER_CAMEL.to(CaseFormat.UPPER_UNDERSCORE, fragment);
        }
    }
    private static class CapitalizeLambda extends CustomLambda {
        @Override
        public String formatFragment(String fragment) {
            return StringUtils.capitalize(fragment);
        }
    }

    public String getNpmName() {
        return npmName;
    }

    public void setNpmName(String npmName) {
        this.npmName = npmName;
    }

    public String getNpmVersion() {
        return npmVersion;
    }

    public void setNpmVersion(String npmVersion) {
        this.npmVersion = npmVersion;
    }

    public String getNpmRepository() {
        return npmRepository;
    }

    public void setNpmRepository(String npmRepository) {
        this.npmRepository = npmRepository;
    }

    public void setOpaqueToken() {
        this.injectionToken = "OpaqueToken";
    }
}

